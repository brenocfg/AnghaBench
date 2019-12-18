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
struct xhci_hcd {void* debugfs_root; void* debugfs_slots; int /*<<< orphan*/  event_ring; int /*<<< orphan*/  cmd_ring; TYPE_2__* cap_regs; int /*<<< orphan*/  regset_list; } ;
struct device {int dummy; } ;
struct TYPE_4__ {struct device* controller; } ;
struct TYPE_6__ {TYPE_1__ self; } ;
struct TYPE_5__ {int /*<<< orphan*/  run_regs_off; int /*<<< orphan*/  hc_capbase; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int HC_LENGTH (int) ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int RTSOFF_MASK ; 
 int /*<<< orphan*/  XHCI_EXT_CAPS_DEBUG ; 
 int /*<<< orphan*/  XHCI_EXT_CAPS_LEGACY ; 
 int /*<<< orphan*/  XHCI_EXT_CAPS_PROTOCOL ; 
 void* debugfs_create_dir (char*,void*) ; 
 char* dev_name (struct device*) ; 
 int readl (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xhci_cap_regs ; 
 int /*<<< orphan*/  xhci_debugfs_create_ports (struct xhci_hcd*,void*) ; 
 int /*<<< orphan*/  xhci_debugfs_create_ring_dir (struct xhci_hcd*,int /*<<< orphan*/ *,char*,void*) ; 
 int /*<<< orphan*/  xhci_debugfs_extcap_regset (struct xhci_hcd*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  xhci_debugfs_regset (struct xhci_hcd*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*,char*) ; 
 void* xhci_debugfs_root ; 
 int /*<<< orphan*/  xhci_extcap_dbc ; 
 int /*<<< orphan*/  xhci_extcap_legsup ; 
 int /*<<< orphan*/  xhci_extcap_protocol ; 
 int /*<<< orphan*/  xhci_op_regs ; 
 int /*<<< orphan*/  xhci_runtime_regs ; 
 TYPE_3__* xhci_to_hcd (struct xhci_hcd*) ; 

void xhci_debugfs_init(struct xhci_hcd *xhci)
{
	struct device		*dev = xhci_to_hcd(xhci)->self.controller;

	xhci->debugfs_root = debugfs_create_dir(dev_name(dev),
						xhci_debugfs_root);

	INIT_LIST_HEAD(&xhci->regset_list);

	xhci_debugfs_regset(xhci,
			    0,
			    xhci_cap_regs, ARRAY_SIZE(xhci_cap_regs),
			    xhci->debugfs_root, "reg-cap");

	xhci_debugfs_regset(xhci,
			    HC_LENGTH(readl(&xhci->cap_regs->hc_capbase)),
			    xhci_op_regs, ARRAY_SIZE(xhci_op_regs),
			    xhci->debugfs_root, "reg-op");

	xhci_debugfs_regset(xhci,
			    readl(&xhci->cap_regs->run_regs_off) & RTSOFF_MASK,
			    xhci_runtime_regs, ARRAY_SIZE(xhci_runtime_regs),
			    xhci->debugfs_root, "reg-runtime");

	xhci_debugfs_extcap_regset(xhci, XHCI_EXT_CAPS_LEGACY,
				   xhci_extcap_legsup,
				   ARRAY_SIZE(xhci_extcap_legsup),
				   "reg-ext-legsup");

	xhci_debugfs_extcap_regset(xhci, XHCI_EXT_CAPS_PROTOCOL,
				   xhci_extcap_protocol,
				   ARRAY_SIZE(xhci_extcap_protocol),
				   "reg-ext-protocol");

	xhci_debugfs_extcap_regset(xhci, XHCI_EXT_CAPS_DEBUG,
				   xhci_extcap_dbc,
				   ARRAY_SIZE(xhci_extcap_dbc),
				   "reg-ext-dbc");

	xhci_debugfs_create_ring_dir(xhci, &xhci->cmd_ring,
				     "command-ring",
				     xhci->debugfs_root);

	xhci_debugfs_create_ring_dir(xhci, &xhci->event_ring,
				     "event-ring",
				     xhci->debugfs_root);

	xhci->debugfs_slots = debugfs_create_dir("devices", xhci->debugfs_root);

	xhci_debugfs_create_ports(xhci, xhci->debugfs_root);
}