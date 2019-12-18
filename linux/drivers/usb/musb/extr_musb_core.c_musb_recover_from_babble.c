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
typedef  int /*<<< orphan*/  u8 ;
struct musb {scalar_t__ dyn_fifo; int /*<<< orphan*/  mregs; } ;

/* Variables and functions */
 int /*<<< orphan*/  MUSB_DEVCTL ; 
 int /*<<< orphan*/  MUSB_DEVCTL_SESSION ; 
 int ep_config_from_hw (struct musb*) ; 
 int ep_config_from_table (struct musb*) ; 
 int /*<<< orphan*/  musb_disable_interrupts (struct musb*) ; 
 int /*<<< orphan*/  musb_enable_interrupts (struct musb*) ; 
 int musb_platform_recover (struct musb*) ; 
 int /*<<< orphan*/  musb_readb (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  musb_root_disconnect (struct musb*) ; 
 int /*<<< orphan*/  musb_start (struct musb*) ; 
 int /*<<< orphan*/  musb_writeb (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static void musb_recover_from_babble(struct musb *musb)
{
	int ret;
	u8 devctl;

	musb_disable_interrupts(musb);

	/*
	 * wait at least 320 cycles of 60MHz clock. That's 5.3us, we will give
	 * it some slack and wait for 10us.
	 */
	udelay(10);

	ret  = musb_platform_recover(musb);
	if (ret) {
		musb_enable_interrupts(musb);
		return;
	}

	/* drop session bit */
	devctl = musb_readb(musb->mregs, MUSB_DEVCTL);
	devctl &= ~MUSB_DEVCTL_SESSION;
	musb_writeb(musb->mregs, MUSB_DEVCTL, devctl);

	/* tell usbcore about it */
	musb_root_disconnect(musb);

	/*
	 * When a babble condition occurs, the musb controller
	 * removes the session bit and the endpoint config is lost.
	 */
	if (musb->dyn_fifo)
		ret = ep_config_from_table(musb);
	else
		ret = ep_config_from_hw(musb);

	/* restart session */
	if (ret == 0)
		musb_start(musb);
}