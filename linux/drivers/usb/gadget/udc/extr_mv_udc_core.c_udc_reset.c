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
typedef  int u32 ;
struct mv_udc {int ep_dqh_dma; TYPE_3__* op_regs; scalar_t__ force_fs; TYPE_2__* cap_regs; TYPE_1__* dev; } ;
struct TYPE_6__ {int /*<<< orphan*/ * epctrlx; int /*<<< orphan*/ * portsc; int /*<<< orphan*/  eplistaddr; int /*<<< orphan*/  epsetupstat; int /*<<< orphan*/  usbmode; int /*<<< orphan*/  usbcmd; } ;
struct TYPE_5__ {int /*<<< orphan*/  hcsparams; } ;
struct TYPE_4__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EPCTRL_RX_EP_STALL ; 
 int EPCTRL_TX_EP_STALL ; 
 int ETIMEDOUT ; 
 int HCSPARAMS_PPC ; 
 unsigned int LOOPS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LOOPS_USEC ; 
 int PORTSCX_FORCE_FULL_SPEED_CONNECT ; 
 int PORTSCX_PORT_POWER ; 
 int PORTSCX_W1C_BITS ; 
 int /*<<< orphan*/  RESET_TIMEOUT ; 
 int USBCMD_CTRL_RESET ; 
 int USBCMD_RUN_STOP ; 
 int USBMODE_CTRL_MODE_DEVICE ; 
 int USBMODE_SETUP_LOCK_OFF ; 
 int USB_EP_LIST_ADDRESS_MASK ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int readl (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  udelay (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  writel (int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int udc_reset(struct mv_udc *udc)
{
	unsigned int loops;
	u32 tmp, portsc;

	/* Stop the controller */
	tmp = readl(&udc->op_regs->usbcmd);
	tmp &= ~USBCMD_RUN_STOP;
	writel(tmp, &udc->op_regs->usbcmd);

	/* Reset the controller to get default values */
	writel(USBCMD_CTRL_RESET, &udc->op_regs->usbcmd);

	/* wait for reset to complete */
	loops = LOOPS(RESET_TIMEOUT);
	while (readl(&udc->op_regs->usbcmd) & USBCMD_CTRL_RESET) {
		if (loops == 0) {
			dev_err(&udc->dev->dev,
				"Wait for RESET completed TIMEOUT\n");
			return -ETIMEDOUT;
		}
		loops--;
		udelay(LOOPS_USEC);
	}

	/* set controller to device mode */
	tmp = readl(&udc->op_regs->usbmode);
	tmp |= USBMODE_CTRL_MODE_DEVICE;

	/* turn setup lockout off, require setup tripwire in usbcmd */
	tmp |= USBMODE_SETUP_LOCK_OFF;

	writel(tmp, &udc->op_regs->usbmode);

	writel(0x0, &udc->op_regs->epsetupstat);

	/* Configure the Endpoint List Address */
	writel(udc->ep_dqh_dma & USB_EP_LIST_ADDRESS_MASK,
		&udc->op_regs->eplistaddr);

	portsc = readl(&udc->op_regs->portsc[0]);
	if (readl(&udc->cap_regs->hcsparams) & HCSPARAMS_PPC)
		portsc &= (~PORTSCX_W1C_BITS | ~PORTSCX_PORT_POWER);

	if (udc->force_fs)
		portsc |= PORTSCX_FORCE_FULL_SPEED_CONNECT;
	else
		portsc &= (~PORTSCX_FORCE_FULL_SPEED_CONNECT);

	writel(portsc, &udc->op_regs->portsc[0]);

	tmp = readl(&udc->op_regs->epctrlx[0]);
	tmp &= ~(EPCTRL_TX_EP_STALL | EPCTRL_RX_EP_STALL);
	writel(tmp, &udc->op_regs->epctrlx[0]);

	return 0;
}