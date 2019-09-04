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
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u32 ;
struct be_mcc_wrb {int dummy; } ;
struct be_cmd_resp_get_beacon_state {int /*<<< orphan*/  beacon_state; } ;
struct be_cmd_req_get_beacon_state {int /*<<< orphan*/  port_num; int /*<<< orphan*/  hdr; } ;
struct be_adapter {int /*<<< orphan*/  mcc_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  CMD_SUBSYSTEM_COMMON ; 
 int EBUSY ; 
 int /*<<< orphan*/  OPCODE_COMMON_GET_BEACON_STATE ; 
 int be_mcc_notify_wait (struct be_adapter*) ; 
 int /*<<< orphan*/  be_wrb_cmd_hdr_prepare (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,struct be_mcc_wrb*,int /*<<< orphan*/ *) ; 
 void* embedded_payload (struct be_mcc_wrb*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct be_mcc_wrb* wrb_from_mccq (struct be_adapter*) ; 

int be_cmd_get_beacon_state(struct be_adapter *adapter, u8 port_num, u32 *state)
{
	struct be_mcc_wrb *wrb;
	struct be_cmd_req_get_beacon_state *req;
	int status;

	mutex_lock(&adapter->mcc_lock);

	wrb = wrb_from_mccq(adapter);
	if (!wrb) {
		status = -EBUSY;
		goto err;
	}
	req = embedded_payload(wrb);

	be_wrb_cmd_hdr_prepare(&req->hdr, CMD_SUBSYSTEM_COMMON,
			       OPCODE_COMMON_GET_BEACON_STATE, sizeof(*req),
			       wrb, NULL);

	req->port_num = port_num;

	status = be_mcc_notify_wait(adapter);
	if (!status) {
		struct be_cmd_resp_get_beacon_state *resp =
						embedded_payload(wrb);

		*state = resp->beacon_state;
	}

err:
	mutex_unlock(&adapter->mcc_lock);
	return status;
}