#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct tidaw {int cpmode; int expires; int /*<<< orphan*/  flags; int /*<<< orphan*/  status; int /*<<< orphan*/  buildclk; int /*<<< orphan*/  retries; struct dasd_device* basedev; struct dasd_device* memdev; struct dasd_device* startdev; int /*<<< orphan*/  cpaddr; int /*<<< orphan*/  data; } ;
struct itcw {int cpmode; int expires; int /*<<< orphan*/  flags; int /*<<< orphan*/  status; int /*<<< orphan*/  buildclk; int /*<<< orphan*/  retries; struct dasd_device* basedev; struct dasd_device* memdev; struct dasd_device* startdev; int /*<<< orphan*/  cpaddr; int /*<<< orphan*/  data; } ;
struct format_data_t {int stop_unit; int start_unit; } ;
struct eckd_count {int dummy; } ;
struct dasd_eckd_private {int /*<<< orphan*/  count; } ;
struct dasd_device {int default_expires; int /*<<< orphan*/  default_retries; struct dasd_eckd_private* private; } ;
struct dasd_ccw_req {int cpmode; int expires; int /*<<< orphan*/  flags; int /*<<< orphan*/  status; int /*<<< orphan*/  buildclk; int /*<<< orphan*/  retries; struct dasd_device* basedev; struct dasd_device* memdev; struct dasd_device* startdev; int /*<<< orphan*/  cpaddr; int /*<<< orphan*/  data; } ;

/* Variables and functions */
 int /*<<< orphan*/  DASD_CQR_FILLED ; 
 int /*<<< orphan*/  DASD_CQR_SUPPRESS_FP ; 
 int /*<<< orphan*/  DASD_CQR_SUPPRESS_IL ; 
 int /*<<< orphan*/  DASD_ECKD_CCW_READ_COUNT_MT ; 
 int /*<<< orphan*/  DASD_ECKD_MAGIC ; 
 int EINVAL ; 
 struct tidaw* ERR_PTR (int) ; 
 int HZ ; 
 scalar_t__ IS_ERR (struct tidaw*) ; 
 int /*<<< orphan*/  ITCW_OP_READ ; 
 int /*<<< orphan*/  TIDAW_FLAGS_LAST ; 
 struct dasd_device* dasd_alias_get_start_dev (struct dasd_device*) ; 
 struct tidaw* dasd_fmalloc_request (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,struct dasd_device*) ; 
 int /*<<< orphan*/  dasd_sfree_request (struct tidaw*,struct dasd_device*) ; 
 int /*<<< orphan*/  get_tod_clock () ; 
 struct tidaw* itcw_add_tidaw (struct tidaw*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int itcw_calc_size (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  itcw_finalize (struct tidaw*) ; 
 int /*<<< orphan*/  itcw_get_tcw (struct tidaw*) ; 
 struct tidaw* itcw_init (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int prepare_itcw (struct tidaw*,int,int,int /*<<< orphan*/ ,struct dasd_device*,struct dasd_device*,int /*<<< orphan*/ ,int,int,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static struct dasd_ccw_req *
dasd_eckd_build_check_tcw(struct dasd_device *base, struct format_data_t *fdata,
			  int enable_pav, struct eckd_count *fmt_buffer,
			  int rpt)
{
	struct dasd_eckd_private *start_priv;
	struct dasd_device *startdev = NULL;
	struct tidaw *last_tidaw = NULL;
	struct dasd_ccw_req *cqr;
	struct itcw *itcw;
	int itcw_size;
	int count;
	int rc;
	int i;

	if (enable_pav)
		startdev = dasd_alias_get_start_dev(base);

	if (!startdev)
		startdev = base;

	start_priv = startdev->private;

	count = rpt * (fdata->stop_unit - fdata->start_unit + 1);

	/*
	 * we're adding 'count' amount of tidaw to the itcw.
	 * calculate the corresponding itcw_size
	 */
	itcw_size = itcw_calc_size(0, count, 0);

	cqr = dasd_fmalloc_request(DASD_ECKD_MAGIC, 0, itcw_size, startdev);
	if (IS_ERR(cqr))
		return cqr;

	start_priv->count++;

	itcw = itcw_init(cqr->data, itcw_size, ITCW_OP_READ, 0, count, 0);
	if (IS_ERR(itcw)) {
		rc = -EINVAL;
		goto out_err;
	}

	cqr->cpaddr = itcw_get_tcw(itcw);
	rc = prepare_itcw(itcw, fdata->start_unit, fdata->stop_unit,
			  DASD_ECKD_CCW_READ_COUNT_MT, base, startdev, 0, count,
			  sizeof(struct eckd_count),
			  count * sizeof(struct eckd_count), 0, rpt);
	if (rc)
		goto out_err;

	for (i = 0; i < count; i++) {
		last_tidaw = itcw_add_tidaw(itcw, 0, fmt_buffer++,
					    sizeof(struct eckd_count));
		if (IS_ERR(last_tidaw)) {
			rc = -EINVAL;
			goto out_err;
		}
	}

	last_tidaw->flags |= TIDAW_FLAGS_LAST;
	itcw_finalize(itcw);

	cqr->cpmode = 1;
	cqr->startdev = startdev;
	cqr->memdev = startdev;
	cqr->basedev = base;
	cqr->retries = startdev->default_retries;
	cqr->expires = startdev->default_expires * HZ;
	cqr->buildclk = get_tod_clock();
	cqr->status = DASD_CQR_FILLED;
	/* Set flags to suppress output for expected errors */
	set_bit(DASD_CQR_SUPPRESS_FP, &cqr->flags);
	set_bit(DASD_CQR_SUPPRESS_IL, &cqr->flags);

	return cqr;

out_err:
	dasd_sfree_request(cqr, startdev);

	return ERR_PTR(rc);
}