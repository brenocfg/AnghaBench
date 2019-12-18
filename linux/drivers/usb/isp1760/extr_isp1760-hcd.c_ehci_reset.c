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
typedef  int /*<<< orphan*/  u32 ;
struct usb_hcd {int /*<<< orphan*/  state; int /*<<< orphan*/  regs; } ;
struct isp1760_hcd {int /*<<< orphan*/  next_statechange; } ;

/* Variables and functions */
 int /*<<< orphan*/  CMD_RESET ; 
 int /*<<< orphan*/  HC_STATE_HALT ; 
 int /*<<< orphan*/  HC_USBCMD ; 
 int handshake (struct usb_hcd*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 struct isp1760_hcd* hcd_to_priv (struct usb_hcd*) ; 
 int /*<<< orphan*/  jiffies ; 
 int /*<<< orphan*/  reg_read32 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  reg_write32 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ehci_reset(struct usb_hcd *hcd)
{
	struct isp1760_hcd *priv = hcd_to_priv(hcd);

	u32 command = reg_read32(hcd->regs, HC_USBCMD);

	command |= CMD_RESET;
	reg_write32(hcd->regs, HC_USBCMD, command);
	hcd->state = HC_STATE_HALT;
	priv->next_statechange = jiffies;

	return handshake(hcd, HC_USBCMD, CMD_RESET, 0, 250 * 1000);
}