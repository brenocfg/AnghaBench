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
typedef  int /*<<< orphan*/  u64 ;
struct i40iw_update_sds_info {int dummy; } ;
struct i40iw_sc_dev {struct i40iw_sc_cqp* cqp; } ;
struct i40iw_sc_cqp {int dummy; } ;
typedef  enum i40iw_status_code { ____Placeholder_i40iw_status_code } i40iw_status_code ;

/* Variables and functions */
 int cqp_sds_wqe_fill (struct i40iw_sc_cqp*,struct i40iw_update_sds_info*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i40iw_sc_cqp_post_sq (struct i40iw_sc_cqp*) ; 

__attribute__((used)) static enum i40iw_status_code i40iw_update_pe_sds(struct i40iw_sc_dev *dev,
						  struct i40iw_update_sds_info *info,
						  u64 scratch)
{
	struct i40iw_sc_cqp *cqp = dev->cqp;
	enum i40iw_status_code ret_code;

	ret_code = cqp_sds_wqe_fill(cqp, info, scratch);
	if (!ret_code)
		i40iw_sc_cqp_post_sq(cqp);

	return ret_code;
}