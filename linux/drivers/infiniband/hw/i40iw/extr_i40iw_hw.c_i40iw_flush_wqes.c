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
struct i40iw_sc_qp {int /*<<< orphan*/  flush_code; scalar_t__ term_flags; } ;
struct i40iw_qp_flush_info {int sq; int rq; int /*<<< orphan*/  rq_major_code; int /*<<< orphan*/  rq_minor_code; int /*<<< orphan*/  sq_major_code; int /*<<< orphan*/  sq_minor_code; } ;
struct i40iw_qp {struct i40iw_sc_qp sc_qp; } ;
struct i40iw_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  i40iw_hw_flush_wqes (struct i40iw_device*,struct i40iw_sc_qp*,struct i40iw_qp_flush_info*,int) ; 
 int /*<<< orphan*/  i40iw_set_flush_info (struct i40iw_qp_flush_info*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct i40iw_qp_flush_info*,int /*<<< orphan*/ ,int) ; 

void i40iw_flush_wqes(struct i40iw_device *iwdev, struct i40iw_qp *iwqp)
{
	struct i40iw_qp_flush_info info;
	struct i40iw_qp_flush_info *pinfo = &info;

	struct i40iw_sc_qp *qp = &iwqp->sc_qp;

	memset(pinfo, 0, sizeof(*pinfo));
	info.sq = true;
	info.rq = true;
	if (qp->term_flags) {
		i40iw_set_flush_info(pinfo, &pinfo->sq_minor_code,
				     &pinfo->sq_major_code, qp->flush_code);
		i40iw_set_flush_info(pinfo, &pinfo->rq_minor_code,
				     &pinfo->rq_major_code, qp->flush_code);
	}
	(void)i40iw_hw_flush_wqes(iwdev, &iwqp->sc_qp, &info, true);
}