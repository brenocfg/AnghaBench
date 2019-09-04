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
struct ishtp_device {int /*<<< orphan*/  devc; scalar_t__ recvd_hw_ready; int /*<<< orphan*/  wait_hw_ready; } ;
struct ipc_rst_payload_type {int reset_id; scalar_t__ reserved; } ;

/* Variables and functions */
 int ENODEV ; 
 int HZ ; 
 int /*<<< orphan*/  IPC_REG_ISH2HOST_DRBL ; 
 int /*<<< orphan*/  IPC_REG_ISH_HOST_FWSTS ; 
 int /*<<< orphan*/  MNG_RESET_NOTIFY ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int ipc_send_mng_msg (struct ishtp_device*,int /*<<< orphan*/ ,struct ipc_rst_payload_type*,int) ; 
 int /*<<< orphan*/  ish_reg_read (struct ishtp_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ish_reg_write (struct ishtp_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_host_ready (struct ishtp_device*) ; 
 int /*<<< orphan*/  wait_event_interruptible_timeout (int /*<<< orphan*/ ,scalar_t__,int) ; 

__attribute__((used)) static int _ish_ipc_reset(struct ishtp_device *dev)
{
	struct ipc_rst_payload_type ipc_mng_msg;
	int	rv = 0;

	ipc_mng_msg.reset_id = 1;
	ipc_mng_msg.reserved = 0;

	set_host_ready(dev);

	/* Clear the incoming doorbell */
	ish_reg_write(dev, IPC_REG_ISH2HOST_DRBL, 0);
	/* Flush write to doorbell */
	ish_reg_read(dev, IPC_REG_ISH_HOST_FWSTS);

	dev->recvd_hw_ready = 0;

	/* send message */
	rv = ipc_send_mng_msg(dev, MNG_RESET_NOTIFY, &ipc_mng_msg,
		sizeof(struct ipc_rst_payload_type));
	if (rv) {
		dev_err(dev->devc, "Failed to send IPC MNG_RESET_NOTIFY\n");
		return	rv;
	}

	wait_event_interruptible_timeout(dev->wait_hw_ready,
					 dev->recvd_hw_ready, 2 * HZ);
	if (!dev->recvd_hw_ready) {
		dev_err(dev->devc, "Timed out waiting for HW ready\n");
		rv = -ENODEV;
	}

	return rv;
}