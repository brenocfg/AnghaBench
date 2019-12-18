#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct xhci_virt_device {int /*<<< orphan*/  out_ctx; } ;
struct xhci_slot_ctx {int dummy; } ;
struct xhci_hcd {int quirks; struct xhci_virt_device** devs; int /*<<< orphan*/  lock; int /*<<< orphan*/  num_active_eps; TYPE_1__* cap_regs; } ;
struct xhci_command {int slot_id; scalar_t__ status; int /*<<< orphan*/  completion; } ;
struct TYPE_4__ {int /*<<< orphan*/  controller; } ;
struct usb_hcd {TYPE_2__ self; } ;
struct usb_device {int slot_id; } ;
struct TYPE_3__ {int /*<<< orphan*/  hcs_params1; } ;

/* Variables and functions */
 scalar_t__ COMP_SUCCESS ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  GFP_NOIO ; 
 int /*<<< orphan*/  HCS_MAX_SLOTS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRB_ENABLE_SLOT ; 
 int XHCI_EP_LIMIT_QUIRK ; 
 int XHCI_RESET_ON_RESUME ; 
 struct xhci_hcd* hcd_to_xhci (struct usb_hcd*) ; 
 int /*<<< orphan*/  pm_runtime_get_noresume (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  readl (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  trace_xhci_alloc_dev (struct xhci_slot_ctx*) ; 
 int /*<<< orphan*/  wait_for_completion (int /*<<< orphan*/ ) ; 
 struct xhci_command* xhci_alloc_command (struct xhci_hcd*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xhci_alloc_virt_device (struct xhci_hcd*,int,struct usb_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xhci_dbg (struct xhci_hcd*,char*) ; 
 int /*<<< orphan*/  xhci_debugfs_create_slot (struct xhci_hcd*,int) ; 
 int xhci_disable_slot (struct xhci_hcd*,int) ; 
 int /*<<< orphan*/  xhci_err (struct xhci_hcd*,char*,...) ; 
 int /*<<< orphan*/  xhci_free_command (struct xhci_hcd*,struct xhci_command*) ; 
 int /*<<< orphan*/  xhci_free_virt_device (struct xhci_hcd*,int) ; 
 struct xhci_slot_ctx* xhci_get_slot_ctx (struct xhci_hcd*,int /*<<< orphan*/ ) ; 
 int xhci_queue_slot_control (struct xhci_hcd*,struct xhci_command*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int xhci_reserve_host_control_ep_resources (struct xhci_hcd*) ; 
 int /*<<< orphan*/  xhci_ring_cmd_db (struct xhci_hcd*) ; 
 int /*<<< orphan*/  xhci_warn (struct xhci_hcd*,char*,...) ; 

int xhci_alloc_dev(struct usb_hcd *hcd, struct usb_device *udev)
{
	struct xhci_hcd *xhci = hcd_to_xhci(hcd);
	struct xhci_virt_device *vdev;
	struct xhci_slot_ctx *slot_ctx;
	unsigned long flags;
	int ret, slot_id;
	struct xhci_command *command;

	command = xhci_alloc_command(xhci, true, GFP_KERNEL);
	if (!command)
		return 0;

	spin_lock_irqsave(&xhci->lock, flags);
	ret = xhci_queue_slot_control(xhci, command, TRB_ENABLE_SLOT, 0);
	if (ret) {
		spin_unlock_irqrestore(&xhci->lock, flags);
		xhci_dbg(xhci, "FIXME: allocate a command ring segment\n");
		xhci_free_command(xhci, command);
		return 0;
	}
	xhci_ring_cmd_db(xhci);
	spin_unlock_irqrestore(&xhci->lock, flags);

	wait_for_completion(command->completion);
	slot_id = command->slot_id;

	if (!slot_id || command->status != COMP_SUCCESS) {
		xhci_err(xhci, "Error while assigning device slot ID\n");
		xhci_err(xhci, "Max number of devices this xHCI host supports is %u.\n",
				HCS_MAX_SLOTS(
					readl(&xhci->cap_regs->hcs_params1)));
		xhci_free_command(xhci, command);
		return 0;
	}

	xhci_free_command(xhci, command);

	if ((xhci->quirks & XHCI_EP_LIMIT_QUIRK)) {
		spin_lock_irqsave(&xhci->lock, flags);
		ret = xhci_reserve_host_control_ep_resources(xhci);
		if (ret) {
			spin_unlock_irqrestore(&xhci->lock, flags);
			xhci_warn(xhci, "Not enough host resources, "
					"active endpoint contexts = %u\n",
					xhci->num_active_eps);
			goto disable_slot;
		}
		spin_unlock_irqrestore(&xhci->lock, flags);
	}
	/* Use GFP_NOIO, since this function can be called from
	 * xhci_discover_or_reset_device(), which may be called as part of
	 * mass storage driver error handling.
	 */
	if (!xhci_alloc_virt_device(xhci, slot_id, udev, GFP_NOIO)) {
		xhci_warn(xhci, "Could not allocate xHCI USB device data structures\n");
		goto disable_slot;
	}
	vdev = xhci->devs[slot_id];
	slot_ctx = xhci_get_slot_ctx(xhci, vdev->out_ctx);
	trace_xhci_alloc_dev(slot_ctx);

	udev->slot_id = slot_id;

	xhci_debugfs_create_slot(xhci, slot_id);

#ifndef CONFIG_USB_DEFAULT_PERSIST
	/*
	 * If resetting upon resume, we can't put the controller into runtime
	 * suspend if there is a device attached.
	 */
	if (xhci->quirks & XHCI_RESET_ON_RESUME)
		pm_runtime_get_noresume(hcd->self.controller);
#endif

	/* Is this a LS or FS device under a HS hub? */
	/* Hub or peripherial? */
	return 1;

disable_slot:
	ret = xhci_disable_slot(xhci, udev->slot_id);
	if (ret)
		xhci_free_virt_device(xhci, udev->slot_id);

	return 0;
}