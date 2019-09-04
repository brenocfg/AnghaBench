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
typedef  int u32 ;
struct acpi_ipmi_msg {int /*<<< orphan*/  tx_complete; int /*<<< orphan*/  tx_message; int /*<<< orphan*/  tx_msgid; int /*<<< orphan*/  addr; int /*<<< orphan*/  head; struct acpi_ipmi_device* device; } ;
struct acpi_ipmi_device {int /*<<< orphan*/  user_interface; int /*<<< orphan*/  tx_msg_lock; int /*<<< orphan*/  tx_msg_list; scalar_t__ dead; } ;
typedef  int /*<<< orphan*/  acpi_status ;
typedef  int /*<<< orphan*/  acpi_physical_address ;
typedef  int /*<<< orphan*/  acpi_integer ;
struct TYPE_2__ {int /*<<< orphan*/  ipmi_lock; } ;

/* Variables and functions */
 int ACPI_IO_MASK ; 
 int ACPI_READ ; 
 int /*<<< orphan*/  AE_ERROR ; 
 int /*<<< orphan*/  AE_NOT_EXIST ; 
 int /*<<< orphan*/  AE_OK ; 
 int /*<<< orphan*/  AE_TYPE ; 
 int /*<<< orphan*/  IPMI_TIMEOUT ; 
 scalar_t__ acpi_format_ipmi_request (struct acpi_ipmi_msg*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  acpi_format_ipmi_response (struct acpi_ipmi_msg*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  acpi_ipmi_msg_get (struct acpi_ipmi_msg*) ; 
 int /*<<< orphan*/  acpi_ipmi_msg_put (struct acpi_ipmi_msg*) ; 
 TYPE_1__ driver_data ; 
 int /*<<< orphan*/  ipmi_cancel_tx_msg (struct acpi_ipmi_device*,struct acpi_ipmi_msg*) ; 
 struct acpi_ipmi_msg* ipmi_msg_alloc () ; 
 int /*<<< orphan*/  ipmi_msg_release (struct acpi_ipmi_msg*) ; 
 int ipmi_request_settime (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  wait_for_completion (int /*<<< orphan*/ *) ; 

__attribute__((used)) static acpi_status
acpi_ipmi_space_handler(u32 function, acpi_physical_address address,
			u32 bits, acpi_integer *value,
			void *handler_context, void *region_context)
{
	struct acpi_ipmi_msg *tx_msg;
	struct acpi_ipmi_device *ipmi_device;
	int err;
	acpi_status status;
	unsigned long flags;

	/*
	 * IPMI opregion message.
	 * IPMI message is firstly written to the BMC and system software
	 * can get the respsonse. So it is unmeaningful for the read access
	 * of IPMI opregion.
	 */
	if ((function & ACPI_IO_MASK) == ACPI_READ)
		return AE_TYPE;

	tx_msg = ipmi_msg_alloc();
	if (!tx_msg)
		return AE_NOT_EXIST;
	ipmi_device = tx_msg->device;

	if (acpi_format_ipmi_request(tx_msg, address, value) != 0) {
		ipmi_msg_release(tx_msg);
		return AE_TYPE;
	}

	acpi_ipmi_msg_get(tx_msg);
	mutex_lock(&driver_data.ipmi_lock);
	/* Do not add a tx_msg that can not be flushed. */
	if (ipmi_device->dead) {
		mutex_unlock(&driver_data.ipmi_lock);
		ipmi_msg_release(tx_msg);
		return AE_NOT_EXIST;
	}
	spin_lock_irqsave(&ipmi_device->tx_msg_lock, flags);
	list_add_tail(&tx_msg->head, &ipmi_device->tx_msg_list);
	spin_unlock_irqrestore(&ipmi_device->tx_msg_lock, flags);
	mutex_unlock(&driver_data.ipmi_lock);

	err = ipmi_request_settime(ipmi_device->user_interface,
				   &tx_msg->addr,
				   tx_msg->tx_msgid,
				   &tx_msg->tx_message,
				   NULL, 0, 0, IPMI_TIMEOUT);
	if (err) {
		status = AE_ERROR;
		goto out_msg;
	}
	wait_for_completion(&tx_msg->tx_complete);

	acpi_format_ipmi_response(tx_msg, value);
	status = AE_OK;

out_msg:
	ipmi_cancel_tx_msg(ipmi_device, tx_msg);
	acpi_ipmi_msg_put(tx_msg);
	return status;
}