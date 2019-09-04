#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
struct i40iw_local_mac_ipaddr_entry_info {int /*<<< orphan*/  entry_idx; int /*<<< orphan*/  mac_addr; } ;
struct i40iw_cqp {int /*<<< orphan*/  sc_cqp; } ;
struct i40iw_device {struct i40iw_cqp cqp; } ;
struct TYPE_4__ {uintptr_t scratch; int /*<<< orphan*/ * cqp; struct i40iw_local_mac_ipaddr_entry_info info; } ;
struct TYPE_5__ {TYPE_1__ add_local_mac_ipaddr_entry; } ;
struct TYPE_6__ {TYPE_2__ u; } ;
struct cqp_commands_info {int post_sq; TYPE_3__ in; int /*<<< orphan*/  cqp_cmd; } ;
struct i40iw_cqp_request {struct cqp_commands_info info; } ;
typedef  enum i40iw_status_code { ____Placeholder_i40iw_status_code } i40iw_status_code ;

/* Variables and functions */
 int I40IW_ERR_NO_MEMORY ; 
 int /*<<< orphan*/  OP_ADD_LOCAL_MAC_IPADDR_ENTRY ; 
 int /*<<< orphan*/  ether_addr_copy (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct i40iw_cqp_request* i40iw_get_cqp_request (struct i40iw_cqp*,int) ; 
 int i40iw_handle_cqp_op (struct i40iw_device*,struct i40iw_cqp_request*) ; 
 int /*<<< orphan*/  i40iw_pr_err (char*) ; 

__attribute__((used)) static enum i40iw_status_code i40iw_add_mac_ipaddr_entry(struct i40iw_device *iwdev,
							 u8 *mac_addr,
							 u8 idx)
{
	struct i40iw_local_mac_ipaddr_entry_info *info;
	struct i40iw_cqp *iwcqp = &iwdev->cqp;
	struct i40iw_cqp_request *cqp_request;
	struct cqp_commands_info *cqp_info;
	enum i40iw_status_code status = 0;

	cqp_request = i40iw_get_cqp_request(iwcqp, true);
	if (!cqp_request) {
		i40iw_pr_err("cqp_request memory failed\n");
		return I40IW_ERR_NO_MEMORY;
	}

	cqp_info = &cqp_request->info;

	cqp_info->post_sq = 1;
	info = &cqp_info->in.u.add_local_mac_ipaddr_entry.info;
	ether_addr_copy(info->mac_addr, mac_addr);
	info->entry_idx = idx;
	cqp_info->in.u.add_local_mac_ipaddr_entry.scratch = (uintptr_t)cqp_request;
	cqp_info->cqp_cmd = OP_ADD_LOCAL_MAC_IPADDR_ENTRY;
	cqp_info->in.u.add_local_mac_ipaddr_entry.cqp = &iwcqp->sc_cqp;
	cqp_info->in.u.add_local_mac_ipaddr_entry.scratch = (uintptr_t)cqp_request;
	status = i40iw_handle_cqp_op(iwdev, cqp_request);
	if (status)
		i40iw_pr_err("CQP-OP Add MAC Ip entry fail");
	return status;
}