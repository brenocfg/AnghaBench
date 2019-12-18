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
struct TYPE_3__ {size_t type; } ;
struct bttv {int /*<<< orphan*/  ctrl_handler; TYPE_1__ c; } ;
struct TYPE_4__ {scalar_t__ no_video; } ;

/* Variables and functions */
 int /*<<< orphan*/  BT848_CAP_CTL ; 
 int /*<<< orphan*/  BT848_COLOR_CTL ; 
 int BT848_COLOR_CTL_GAMMA ; 
 int /*<<< orphan*/  BT848_E_VSCALE_HI ; 
 int /*<<< orphan*/  BT848_GPIO_DMA_CTL ; 
 int BT848_GPIO_DMA_CTL_GPINTC ; 
 int BT848_GPIO_DMA_CTL_GPINTI ; 
 int BT848_GPIO_DMA_CTL_PKTP_32 ; 
 int BT848_GPIO_DMA_CTL_PLTP1_16 ; 
 int BT848_GPIO_DMA_CTL_PLTP23_16 ; 
 int /*<<< orphan*/  BT848_IFORM ; 
 int BT848_IFORM_AUTO ; 
 int BT848_IFORM_XTAUTO ; 
 int /*<<< orphan*/  BT848_O_VSCALE_HI ; 
 TYPE_2__* bttv_tvcards ; 
 int /*<<< orphan*/  btwrite (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  init_irqreg (struct bttv*) ; 
 int /*<<< orphan*/  v4l2_ctrl_handler_setup (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void init_bt848(struct bttv *btv)
{
	if (bttv_tvcards[btv->c.type].no_video) {
		/* very basic init only */
		init_irqreg(btv);
		return;
	}

	btwrite(0x00, BT848_CAP_CTL);
	btwrite(BT848_COLOR_CTL_GAMMA, BT848_COLOR_CTL);
	btwrite(BT848_IFORM_XTAUTO | BT848_IFORM_AUTO, BT848_IFORM);

	/* set planar and packed mode trigger points and         */
	/* set rising edge of inverted GPINTR pin as irq trigger */
	btwrite(BT848_GPIO_DMA_CTL_PKTP_32|
		BT848_GPIO_DMA_CTL_PLTP1_16|
		BT848_GPIO_DMA_CTL_PLTP23_16|
		BT848_GPIO_DMA_CTL_GPINTC|
		BT848_GPIO_DMA_CTL_GPINTI,
		BT848_GPIO_DMA_CTL);

	btwrite(0x20, BT848_E_VSCALE_HI);
	btwrite(0x20, BT848_O_VSCALE_HI);

	v4l2_ctrl_handler_setup(&btv->ctrl_handler);

	/* interrupt */
	init_irqreg(btv);
}