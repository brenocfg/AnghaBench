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
struct usb_hcd {int dummy; } ;
struct mbus_dram_window {int size; int mbus_attr; int base; } ;
struct mbus_dram_target_info {int num_cs; int mbus_dram_target_id; struct mbus_dram_window* cs; } ;

/* Variables and functions */
 int /*<<< orphan*/  USB_WINDOW_BASE (int) ; 
 int /*<<< orphan*/  USB_WINDOW_CTRL (int) ; 
 int /*<<< orphan*/  wrl (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
ehci_orion_conf_mbus_windows(struct usb_hcd *hcd,
			     const struct mbus_dram_target_info *dram)
{
	int i;

	for (i = 0; i < 4; i++) {
		wrl(USB_WINDOW_CTRL(i), 0);
		wrl(USB_WINDOW_BASE(i), 0);
	}

	for (i = 0; i < dram->num_cs; i++) {
		const struct mbus_dram_window *cs = dram->cs + i;

		wrl(USB_WINDOW_CTRL(i), ((cs->size - 1) & 0xffff0000) |
					(cs->mbus_attr << 8) |
					(dram->mbus_dram_target_id << 4) | 1);
		wrl(USB_WINDOW_BASE(i), cs->base);
	}
}