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
struct kernel_ipmi_msg {int netfn; int cmd; unsigned char* data; int data_len; } ;
struct ipmi_system_interface_addr {scalar_t__ lun; void* channel; void* addr_type; } ;
struct ipmi_smi {int event_receiver; TYPE_1__* addrinfo; scalar_t__ local_sel_device; int /*<<< orphan*/  event_receiver_lun; int /*<<< orphan*/ * null_user_handler; scalar_t__ local_event_generator; } ;
struct ipmi_ipmb_addr {int slave_addr; int /*<<< orphan*/  lun; scalar_t__ channel; int /*<<< orphan*/  addr_type; } ;
struct ipmi_addr {int dummy; } ;
struct TYPE_2__ {int address; } ;

/* Variables and functions */
 int IPMI_ADD_SEL_ENTRY_CMD ; 
 void* IPMI_BMC_CHANNEL ; 
 int IPMI_GET_DEVICE_ID_CMD ; 
 int IPMI_GET_EVENT_RECEIVER_CMD ; 
 int /*<<< orphan*/  IPMI_IPMB_ADDR_TYPE ; 
 int IPMI_NETFN_APP_REQUEST ; 
 int IPMI_NETFN_SENSOR_EVENT_REQUEST ; 
 int IPMI_NETFN_STORAGE_REQUEST ; 
 scalar_t__ IPMI_SEND_PANIC_EVENT_NONE ; 
 scalar_t__ IPMI_SEND_PANIC_EVENT_STRING ; 
 void* IPMI_SYSTEM_INTERFACE_ADDR_TYPE ; 
 int /*<<< orphan*/ * device_id_fetcher ; 
 int /*<<< orphan*/ * event_receiver_fetcher ; 
 int /*<<< orphan*/  ipmi_panic_request_and_wait (struct ipmi_smi*,struct ipmi_addr*,struct kernel_ipmi_msg*) ; 
 scalar_t__ ipmi_send_panic_event ; 
 int /*<<< orphan*/  smp_rmb () ; 
 int strlen (char*) ; 
 int /*<<< orphan*/  strncpy (unsigned char*,char*,int) ; 

__attribute__((used)) static void send_panic_events(struct ipmi_smi *intf, char *str)
{
	struct kernel_ipmi_msg msg;
	unsigned char data[16];
	struct ipmi_system_interface_addr *si;
	struct ipmi_addr addr;
	char *p = str;
	struct ipmi_ipmb_addr *ipmb;
	int j;

	if (ipmi_send_panic_event == IPMI_SEND_PANIC_EVENT_NONE)
		return;

	si = (struct ipmi_system_interface_addr *) &addr;
	si->addr_type = IPMI_SYSTEM_INTERFACE_ADDR_TYPE;
	si->channel = IPMI_BMC_CHANNEL;
	si->lun = 0;

	/* Fill in an event telling that we have failed. */
	msg.netfn = 0x04; /* Sensor or Event. */
	msg.cmd = 2; /* Platform event command. */
	msg.data = data;
	msg.data_len = 8;
	data[0] = 0x41; /* Kernel generator ID, IPMI table 5-4 */
	data[1] = 0x03; /* This is for IPMI 1.0. */
	data[2] = 0x20; /* OS Critical Stop, IPMI table 36-3 */
	data[4] = 0x6f; /* Sensor specific, IPMI table 36-1 */
	data[5] = 0xa1; /* Runtime stop OEM bytes 2 & 3. */

	/*
	 * Put a few breadcrumbs in.  Hopefully later we can add more things
	 * to make the panic events more useful.
	 */
	if (str) {
		data[3] = str[0];
		data[6] = str[1];
		data[7] = str[2];
	}

	/* Send the event announcing the panic. */
	ipmi_panic_request_and_wait(intf, &addr, &msg);

	/*
	 * On every interface, dump a bunch of OEM event holding the
	 * string.
	 */
	if (ipmi_send_panic_event != IPMI_SEND_PANIC_EVENT_STRING || !str)
		return;

	/*
	 * intf_num is used as an marker to tell if the
	 * interface is valid.  Thus we need a read barrier to
	 * make sure data fetched before checking intf_num
	 * won't be used.
	 */
	smp_rmb();

	/*
	 * First job here is to figure out where to send the
	 * OEM events.  There's no way in IPMI to send OEM
	 * events using an event send command, so we have to
	 * find the SEL to put them in and stick them in
	 * there.
	 */

	/* Get capabilities from the get device id. */
	intf->local_sel_device = 0;
	intf->local_event_generator = 0;
	intf->event_receiver = 0;

	/* Request the device info from the local MC. */
	msg.netfn = IPMI_NETFN_APP_REQUEST;
	msg.cmd = IPMI_GET_DEVICE_ID_CMD;
	msg.data = NULL;
	msg.data_len = 0;
	intf->null_user_handler = device_id_fetcher;
	ipmi_panic_request_and_wait(intf, &addr, &msg);

	if (intf->local_event_generator) {
		/* Request the event receiver from the local MC. */
		msg.netfn = IPMI_NETFN_SENSOR_EVENT_REQUEST;
		msg.cmd = IPMI_GET_EVENT_RECEIVER_CMD;
		msg.data = NULL;
		msg.data_len = 0;
		intf->null_user_handler = event_receiver_fetcher;
		ipmi_panic_request_and_wait(intf, &addr, &msg);
	}
	intf->null_user_handler = NULL;

	/*
	 * Validate the event receiver.  The low bit must not
	 * be 1 (it must be a valid IPMB address), it cannot
	 * be zero, and it must not be my address.
	 */
	if (((intf->event_receiver & 1) == 0)
	    && (intf->event_receiver != 0)
	    && (intf->event_receiver != intf->addrinfo[0].address)) {
		/*
		 * The event receiver is valid, send an IPMB
		 * message.
		 */
		ipmb = (struct ipmi_ipmb_addr *) &addr;
		ipmb->addr_type = IPMI_IPMB_ADDR_TYPE;
		ipmb->channel = 0; /* FIXME - is this right? */
		ipmb->lun = intf->event_receiver_lun;
		ipmb->slave_addr = intf->event_receiver;
	} else if (intf->local_sel_device) {
		/*
		 * The event receiver was not valid (or was
		 * me), but I am an SEL device, just dump it
		 * in my SEL.
		 */
		si = (struct ipmi_system_interface_addr *) &addr;
		si->addr_type = IPMI_SYSTEM_INTERFACE_ADDR_TYPE;
		si->channel = IPMI_BMC_CHANNEL;
		si->lun = 0;
	} else
		return; /* No where to send the event. */

	msg.netfn = IPMI_NETFN_STORAGE_REQUEST; /* Storage. */
	msg.cmd = IPMI_ADD_SEL_ENTRY_CMD;
	msg.data = data;
	msg.data_len = 16;

	j = 0;
	while (*p) {
		int size = strlen(p);

		if (size > 11)
			size = 11;
		data[0] = 0;
		data[1] = 0;
		data[2] = 0xf0; /* OEM event without timestamp. */
		data[3] = intf->addrinfo[0].address;
		data[4] = j++; /* sequence # */
		/*
		 * Always give 11 bytes, so strncpy will fill
		 * it with zeroes for me.
		 */
		strncpy(data+5, p, 11);
		p += size;

		ipmi_panic_request_and_wait(intf, &addr, &msg);
	}
}