#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct format_data_t {int stop_unit; int start_unit; } ;
struct eckd_count {int dummy; } ;
struct TYPE_2__ {int* feature; } ;
struct dasd_eckd_private {int /*<<< orphan*/  count; TYPE_1__ features; } ;
struct dasd_device {int default_expires; struct dasd_eckd_private* private; } ;
struct dasd_ccw_req {int expires; int /*<<< orphan*/  flags; int /*<<< orphan*/  status; int /*<<< orphan*/  buildclk; int /*<<< orphan*/  retries; struct dasd_device* basedev; struct dasd_device* memdev; struct dasd_device* startdev; struct ccw1* cpaddr; void* data; } ;
struct ccw1 {int count; scalar_t__ cda; int /*<<< orphan*/  flags; int /*<<< orphan*/  cmd_code; } ;
struct PFX_eckd_data {int dummy; } ;
struct LO_eckd_data {int dummy; } ;
struct DE_eckd_data {int dummy; } ;
typedef  scalar_t__ addr_t ;
typedef  scalar_t__ __u32 ;

/* Variables and functions */
 int /*<<< orphan*/  CCW_FLAG_CC ; 
 int /*<<< orphan*/  CCW_FLAG_SLI ; 
 int /*<<< orphan*/  DASD_CQR_FILLED ; 
 int /*<<< orphan*/  DASD_CQR_SUPPRESS_NRF ; 
 int /*<<< orphan*/  DASD_ECKD_CCW_READ_COUNT ; 
 int /*<<< orphan*/  DASD_ECKD_MAGIC ; 
 int /*<<< orphan*/  DASD_RETRIES ; 
 int HZ ; 
 scalar_t__ IS_ERR (struct dasd_ccw_req*) ; 
 struct dasd_device* dasd_alias_get_start_dev (struct dasd_device*) ; 
 struct dasd_ccw_req* dasd_fmalloc_request (int /*<<< orphan*/ ,int,int,struct dasd_device*) ; 
 int /*<<< orphan*/  define_extent (int /*<<< orphan*/ ,void*,int,int,int /*<<< orphan*/ ,struct dasd_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_tod_clock () ; 
 int /*<<< orphan*/  locate_record (int /*<<< orphan*/ ,void*,int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,struct dasd_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  prefix_LRE (int /*<<< orphan*/ ,void*,int,int,int /*<<< orphan*/ ,struct dasd_device*,struct dasd_device*,int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static struct dasd_ccw_req *
dasd_eckd_build_check(struct dasd_device *base, struct format_data_t *fdata,
		      int enable_pav, struct eckd_count *fmt_buffer, int rpt)
{
	struct dasd_eckd_private *start_priv;
	struct dasd_eckd_private *base_priv;
	struct dasd_device *startdev = NULL;
	struct dasd_ccw_req *cqr;
	struct ccw1 *ccw;
	void *data;
	int cplength, datasize;
	int use_prefix;
	int count;
	int i;

	if (enable_pav)
		startdev = dasd_alias_get_start_dev(base);

	if (!startdev)
		startdev = base;

	start_priv = startdev->private;
	base_priv = base->private;

	count = rpt * (fdata->stop_unit - fdata->start_unit + 1);

	use_prefix = base_priv->features.feature[8] & 0x01;

	if (use_prefix) {
		cplength = 1;
		datasize = sizeof(struct PFX_eckd_data);
	} else {
		cplength = 2;
		datasize = sizeof(struct DE_eckd_data) +
			sizeof(struct LO_eckd_data);
	}
	cplength += count;

	cqr = dasd_fmalloc_request(DASD_ECKD_MAGIC, cplength, datasize, startdev);
	if (IS_ERR(cqr))
		return cqr;

	start_priv->count++;
	data = cqr->data;
	ccw = cqr->cpaddr;

	if (use_prefix) {
		prefix_LRE(ccw++, data, fdata->start_unit, fdata->stop_unit,
			   DASD_ECKD_CCW_READ_COUNT, base, startdev, 1, 0,
			   count, 0, 0);
	} else {
		define_extent(ccw++, data, fdata->start_unit, fdata->stop_unit,
			      DASD_ECKD_CCW_READ_COUNT, startdev, 0);

		data += sizeof(struct DE_eckd_data);
		ccw[-1].flags |= CCW_FLAG_CC;

		locate_record(ccw++, data, fdata->start_unit, 0, count,
			      DASD_ECKD_CCW_READ_COUNT, base, 0);
	}

	for (i = 0; i < count; i++) {
		ccw[-1].flags |= CCW_FLAG_CC;
		ccw->cmd_code = DASD_ECKD_CCW_READ_COUNT;
		ccw->flags = CCW_FLAG_SLI;
		ccw->count = 8;
		ccw->cda = (__u32)(addr_t) fmt_buffer;
		ccw++;
		fmt_buffer++;
	}

	cqr->startdev = startdev;
	cqr->memdev = startdev;
	cqr->basedev = base;
	cqr->retries = DASD_RETRIES;
	cqr->expires = startdev->default_expires * HZ;
	cqr->buildclk = get_tod_clock();
	cqr->status = DASD_CQR_FILLED;
	/* Set flags to suppress output for expected errors */
	set_bit(DASD_CQR_SUPPRESS_NRF, &cqr->flags);

	return cqr;
}