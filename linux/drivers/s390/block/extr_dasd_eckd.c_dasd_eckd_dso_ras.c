#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
typedef  int u16 ;
struct request {int dummy; } ;
struct dasd_rssd_features {int* feature; } ;
struct TYPE_8__ {int trk_per_cyl; } ;
struct dasd_eckd_private {TYPE_4__ rdc_data; TYPE_3__* ned; struct dasd_rssd_features features; } ;
struct dasd_dso_ras_ext_range {int /*<<< orphan*/  end_ext; int /*<<< orphan*/  beg_ext; } ;
struct TYPE_6__ {int by_extent; int guarantee_init; } ;
struct TYPE_5__ {scalar_t__ vol_type; } ;
struct dasd_dso_ras_data {int nr_exts; int /*<<< orphan*/  dev_addr; int /*<<< orphan*/  lss; TYPE_2__ op_flags; TYPE_1__ flags; int /*<<< orphan*/  order; } ;
struct dasd_device {int default_expires; int /*<<< orphan*/  cdev; struct dasd_eckd_private* private; } ;
struct dasd_ccw_req {int retries; int expires; int /*<<< orphan*/  status; int /*<<< orphan*/  buildclk; struct dasd_block* block; struct dasd_device* memdev; struct dasd_device* startdev; struct dasd_dso_ras_data* data; struct ccw1* cpaddr; } ;
struct dasd_block {int dummy; } ;
struct ccw1 {size_t count; int /*<<< orphan*/  cmd_code; scalar_t__ cda; } ;
typedef  scalar_t__ addr_t ;
typedef  scalar_t__ __u32 ;
struct TYPE_7__ {int /*<<< orphan*/  unit_addr; int /*<<< orphan*/  ID; } ;

/* Variables and functions */
 int /*<<< orphan*/  DASD_CQR_FILLED ; 
 int /*<<< orphan*/  DASD_ECKD_CCW_DSO ; 
 int /*<<< orphan*/  DASD_ECKD_MAGIC ; 
 int /*<<< orphan*/  DBF_EVENT_DEVID (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  DBF_WARNING ; 
 int /*<<< orphan*/  DSO_ORDER_RAS ; 
 int /*<<< orphan*/  EINVAL ; 
 struct dasd_ccw_req* ERR_PTR (int /*<<< orphan*/ ) ; 
 int HZ ; 
 scalar_t__ IS_ERR (struct dasd_ccw_req*) ; 
 int /*<<< orphan*/ * blk_mq_rq_to_pdu (struct request*) ; 
 int count_exts (unsigned int,unsigned int,int) ; 
 int dasd_eckd_ext_size (struct dasd_device*) ; 
 scalar_t__ dasd_eckd_ras_sanity_checks (struct dasd_device*,unsigned int,unsigned int) ; 
 struct dasd_ccw_req* dasd_smalloc_request (int /*<<< orphan*/ ,int,size_t,struct dasd_device*,void*) ; 
 int /*<<< orphan*/  get_tod_clock () ; 
 int /*<<< orphan*/  memset (struct dasd_dso_ras_data*,int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  set_ch_t (int /*<<< orphan*/ *,int,int) ; 

__attribute__((used)) static struct dasd_ccw_req *
dasd_eckd_dso_ras(struct dasd_device *device, struct dasd_block *block,
		  struct request *req, unsigned int first_trk,
		  unsigned int last_trk, int by_extent)
{
	struct dasd_eckd_private *private = device->private;
	struct dasd_dso_ras_ext_range *ras_range;
	struct dasd_rssd_features *features;
	struct dasd_dso_ras_data *ras_data;
	u16 heads, beg_head, end_head;
	int cur_to_trk, cur_from_trk;
	struct dasd_ccw_req *cqr;
	u32 beg_cyl, end_cyl;
	struct ccw1 *ccw;
	int trks_per_ext;
	size_t ras_size;
	size_t size;
	int nr_exts;
	void *rq;
	int i;

	if (dasd_eckd_ras_sanity_checks(device, first_trk, last_trk))
		return ERR_PTR(-EINVAL);

	rq = req ? blk_mq_rq_to_pdu(req) : NULL;

	features = &private->features;

	trks_per_ext = dasd_eckd_ext_size(device) * private->rdc_data.trk_per_cyl;
	nr_exts = 0;
	if (by_extent)
		nr_exts = count_exts(first_trk, last_trk, trks_per_ext);
	ras_size = sizeof(*ras_data);
	size = ras_size + (nr_exts * sizeof(*ras_range));

	cqr = dasd_smalloc_request(DASD_ECKD_MAGIC, 1, size, device, rq);
	if (IS_ERR(cqr)) {
		DBF_EVENT_DEVID(DBF_WARNING, device->cdev, "%s",
				"Could not allocate RAS request");
		return cqr;
	}

	ras_data = cqr->data;
	memset(ras_data, 0, size);

	ras_data->order = DSO_ORDER_RAS;
	ras_data->flags.vol_type = 0; /* CKD volume */
	/* Release specified extents or entire volume */
	ras_data->op_flags.by_extent = by_extent;
	/*
	 * This bit guarantees initialisation of tracks within an extent that is
	 * not fully specified, but is only supported with a certain feature
	 * subset.
	 */
	ras_data->op_flags.guarantee_init = !!(features->feature[56] & 0x01);
	ras_data->lss = private->ned->ID;
	ras_data->dev_addr = private->ned->unit_addr;
	ras_data->nr_exts = nr_exts;

	if (by_extent) {
		heads = private->rdc_data.trk_per_cyl;
		cur_from_trk = first_trk;
		cur_to_trk = first_trk + trks_per_ext -
			(first_trk % trks_per_ext) - 1;
		if (cur_to_trk > last_trk)
			cur_to_trk = last_trk;
		ras_range = (struct dasd_dso_ras_ext_range *)(cqr->data + ras_size);

		for (i = 0; i < nr_exts; i++) {
			beg_cyl = cur_from_trk / heads;
			beg_head = cur_from_trk % heads;
			end_cyl = cur_to_trk / heads;
			end_head = cur_to_trk % heads;

			set_ch_t(&ras_range->beg_ext, beg_cyl, beg_head);
			set_ch_t(&ras_range->end_ext, end_cyl, end_head);

			cur_from_trk = cur_to_trk + 1;
			cur_to_trk = cur_from_trk + trks_per_ext - 1;
			if (cur_to_trk > last_trk)
				cur_to_trk = last_trk;
			ras_range++;
		}
	}

	ccw = cqr->cpaddr;
	ccw->cda = (__u32)(addr_t)cqr->data;
	ccw->cmd_code = DASD_ECKD_CCW_DSO;
	ccw->count = size;

	cqr->startdev = device;
	cqr->memdev = device;
	cqr->block = block;
	cqr->retries = 256;
	cqr->expires = device->default_expires * HZ;
	cqr->buildclk = get_tod_clock();
	cqr->status = DASD_CQR_FILLED;

	return cqr;
}