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
struct usb_gadget {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  frindex; } ;

/* Variables and functions */
 int USB_FRINDEX_MASKS ; 
 TYPE_1__* dr_regs ; 
 int fsl_readl (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int fsl_get_frame(struct usb_gadget *gadget)
{
	return (int)(fsl_readl(&dr_regs->frindex) & USB_FRINDEX_MASKS);
}