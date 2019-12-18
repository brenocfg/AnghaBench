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
struct usb_ctrlrequest {int bRequestType; int bRequest; void* wLength; void* wIndex; void* wValue; } ;
typedef  int /*<<< orphan*/  req ;
struct TYPE_2__ {int /*<<< orphan*/  pids; int /*<<< orphan*/  address; int /*<<< orphan*/  control; } ;

/* Variables and functions */
 int /*<<< orphan*/  DBGP_EPADDR (unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DBGP_GO ; 
 int /*<<< orphan*/  DBGP_LOOPS ; 
 int DBGP_MAX_PACKET ; 
 int /*<<< orphan*/  DBGP_OUT ; 
 int /*<<< orphan*/  DBGP_PID_SET (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int USB_DIR_IN ; 
 int /*<<< orphan*/  USB_PID_DATA0 ; 
 int /*<<< orphan*/  USB_PID_SETUP ; 
 void* cpu_to_le16 (int) ; 
 int dbgp_bulk_read (unsigned int,int /*<<< orphan*/ ,void*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dbgp_len_update (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  dbgp_set_data (struct usb_ctrlrequest*,int) ; 
 int dbgp_wait_until_done (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_1__* ehci_debug ; 
 int /*<<< orphan*/  readl (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int dbgp_control_msg(unsigned devnum, int requesttype,
	int request, int value, int index, void *data, int size)
{
	u32 pids, addr, ctrl;
	struct usb_ctrlrequest req;
	int read;
	int ret;

	read = (requesttype & USB_DIR_IN) != 0;
	if (size > (read ? DBGP_MAX_PACKET : 0))
		return -1;

	/* Compute the control message */
	req.bRequestType = requesttype;
	req.bRequest = request;
	req.wValue = cpu_to_le16(value);
	req.wIndex = cpu_to_le16(index);
	req.wLength = cpu_to_le16(size);

	pids = DBGP_PID_SET(USB_PID_DATA0, USB_PID_SETUP);
	addr = DBGP_EPADDR(devnum, 0);

	ctrl = readl(&ehci_debug->control);
	ctrl = dbgp_len_update(ctrl, sizeof(req));
	ctrl |= DBGP_OUT;
	ctrl |= DBGP_GO;

	/* Send the setup message */
	dbgp_set_data(&req, sizeof(req));
	writel(addr, &ehci_debug->address);
	writel(pids, &ehci_debug->pids);
	ret = dbgp_wait_until_done(ctrl, DBGP_LOOPS);
	if (ret < 0)
		return ret;

	/* Read the result */
	return dbgp_bulk_read(devnum, 0, data, size, DBGP_LOOPS);
}