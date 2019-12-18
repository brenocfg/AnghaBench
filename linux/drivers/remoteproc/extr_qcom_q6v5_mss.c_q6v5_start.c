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
struct rproc {scalar_t__ priv; } ;
struct q6v5 {int running; int /*<<< orphan*/  mpss_size; int /*<<< orphan*/  mpss_phys; int /*<<< orphan*/  mpss_perm; scalar_t__ dump_segment_mask; int /*<<< orphan*/  dev; int /*<<< orphan*/  mba_size; int /*<<< orphan*/  mba_phys; int /*<<< orphan*/  mba_perm; int /*<<< orphan*/  q6v5; } ;

/* Variables and functions */
 int ETIMEDOUT ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  msecs_to_jiffies (int) ; 
 int q6v5_mba_load (struct q6v5*) ; 
 int /*<<< orphan*/  q6v5_mba_reclaim (struct q6v5*) ; 
 int q6v5_mpss_load (struct q6v5*) ; 
 int q6v5_xfer_mem_ownership (struct q6v5*,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int qcom_q6v5_wait_for_start (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int q6v5_start(struct rproc *rproc)
{
	struct q6v5 *qproc = (struct q6v5 *)rproc->priv;
	int xfermemop_ret;
	int ret;

	ret = q6v5_mba_load(qproc);
	if (ret)
		return ret;

	dev_info(qproc->dev, "MBA booted, loading mpss\n");

	ret = q6v5_mpss_load(qproc);
	if (ret)
		goto reclaim_mpss;

	ret = qcom_q6v5_wait_for_start(&qproc->q6v5, msecs_to_jiffies(5000));
	if (ret == -ETIMEDOUT) {
		dev_err(qproc->dev, "start timed out\n");
		goto reclaim_mpss;
	}

	xfermemop_ret = q6v5_xfer_mem_ownership(qproc, &qproc->mba_perm, false,
						qproc->mba_phys,
						qproc->mba_size);
	if (xfermemop_ret)
		dev_err(qproc->dev,
			"Failed to reclaim mba buffer system may become unstable\n");

	/* Reset Dump Segment Mask */
	qproc->dump_segment_mask = 0;
	qproc->running = true;

	return 0;

reclaim_mpss:
	xfermemop_ret = q6v5_xfer_mem_ownership(qproc, &qproc->mpss_perm,
						false, qproc->mpss_phys,
						qproc->mpss_size);
	WARN_ON(xfermemop_ret);
	q6v5_mba_reclaim(qproc);

	return ret;
}