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
struct be_mcc_wrb {int dummy; } ;
struct be_cmd_req_hdr {int dummy; } ;
struct be_adapter {int /*<<< orphan*/  mbox_lock; TYPE_1__* pdev; scalar_t__ db; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  CMD_SUBSYSTEM_COMMON ; 
 int /*<<< orphan*/  OPCODE_COMMON_FUNCTION_RESET ; 
 scalar_t__ SLIPORT_CONTROL_OFFSET ; 
 int /*<<< orphan*/  SLI_PORT_CONTROL_IP_MASK ; 
 int be_mbox_notify_wait (struct be_adapter*) ; 
 int /*<<< orphan*/  be_wrb_cmd_hdr_prepare (struct be_cmd_req_hdr*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,struct be_mcc_wrb*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 struct be_cmd_req_hdr* embedded_payload (struct be_mcc_wrb*) ; 
 int /*<<< orphan*/  iowrite32 (int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ lancer_chip (struct be_adapter*) ; 
 int lancer_wait_ready (struct be_adapter*) ; 
 scalar_t__ mutex_lock_interruptible (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct be_mcc_wrb* wrb_from_mbox (struct be_adapter*) ; 

int be_cmd_reset_function(struct be_adapter *adapter)
{
	struct be_mcc_wrb *wrb;
	struct be_cmd_req_hdr *req;
	int status;

	if (lancer_chip(adapter)) {
		iowrite32(SLI_PORT_CONTROL_IP_MASK,
			  adapter->db + SLIPORT_CONTROL_OFFSET);
		status = lancer_wait_ready(adapter);
		if (status)
			dev_err(&adapter->pdev->dev,
				"Adapter in non recoverable error\n");
		return status;
	}

	if (mutex_lock_interruptible(&adapter->mbox_lock))
		return -1;

	wrb = wrb_from_mbox(adapter);
	req = embedded_payload(wrb);

	be_wrb_cmd_hdr_prepare(req, CMD_SUBSYSTEM_COMMON,
			       OPCODE_COMMON_FUNCTION_RESET, sizeof(*req), wrb,
			       NULL);

	status = be_mbox_notify_wait(adapter);

	mutex_unlock(&adapter->mbox_lock);
	return status;
}