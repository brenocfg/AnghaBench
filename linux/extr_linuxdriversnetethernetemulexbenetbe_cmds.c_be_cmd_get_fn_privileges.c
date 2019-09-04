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
typedef  int /*<<< orphan*/  u32 ;
struct be_mcc_wrb {int dummy; } ;
struct be_cmd_resp_get_fn_privileges {int /*<<< orphan*/  privilege_mask; } ;
struct TYPE_2__ {int /*<<< orphan*/  domain; } ;
struct be_cmd_req_get_fn_privileges {TYPE_1__ hdr; } ;
struct be_adapter {int /*<<< orphan*/  mcc_lock; } ;

/* Variables and functions */
 scalar_t__ BEx_chip (struct be_adapter*) ; 
 int /*<<< orphan*/  CMD_SUBSYSTEM_COMMON ; 
 int EBUSY ; 
 int /*<<< orphan*/  MAX_PRIVILEGES ; 
 int /*<<< orphan*/  OPCODE_COMMON_GET_FN_PRIVILEGES ; 
 scalar_t__ be_is_mc (struct be_adapter*) ; 
 int be_mcc_notify_wait (struct be_adapter*) ; 
 scalar_t__ be_physfn (struct be_adapter*) ; 
 int /*<<< orphan*/  be_wrb_cmd_hdr_prepare (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,struct be_mcc_wrb*,int /*<<< orphan*/ *) ; 
 void* embedded_payload (struct be_mcc_wrb*) ; 
 int /*<<< orphan*/  le32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct be_mcc_wrb* wrb_from_mccq (struct be_adapter*) ; 

int be_cmd_get_fn_privileges(struct be_adapter *adapter, u32 *privilege,
			     u32 domain)
{
	struct be_mcc_wrb *wrb;
	struct be_cmd_req_get_fn_privileges *req;
	int status;

	mutex_lock(&adapter->mcc_lock);

	wrb = wrb_from_mccq(adapter);
	if (!wrb) {
		status = -EBUSY;
		goto err;
	}

	req = embedded_payload(wrb);

	be_wrb_cmd_hdr_prepare(&req->hdr, CMD_SUBSYSTEM_COMMON,
			       OPCODE_COMMON_GET_FN_PRIVILEGES, sizeof(*req),
			       wrb, NULL);

	req->hdr.domain = domain;

	status = be_mcc_notify_wait(adapter);
	if (!status) {
		struct be_cmd_resp_get_fn_privileges *resp =
						embedded_payload(wrb);

		*privilege = le32_to_cpu(resp->privilege_mask);

		/* In UMC mode FW does not return right privileges.
		 * Override with correct privilege equivalent to PF.
		 */
		if (BEx_chip(adapter) && be_is_mc(adapter) &&
		    be_physfn(adapter))
			*privilege = MAX_PRIVILEGES;
	}

err:
	mutex_unlock(&adapter->mcc_lock);
	return status;
}