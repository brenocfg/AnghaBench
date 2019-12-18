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
struct bttv {int triton1; scalar_t__ gpioirq; TYPE_1__ c; } ;
struct TYPE_4__ {scalar_t__ no_video; } ;

/* Variables and functions */
 int BT848_INT_FDSR ; 
 int BT848_INT_FMTCHG ; 
 int BT848_INT_GPINT ; 
 int BT848_INT_HLOCK ; 
 int BT848_INT_I2CDONE ; 
 int /*<<< orphan*/  BT848_INT_MASK ; 
 int BT848_INT_OCERR ; 
 int BT848_INT_RISCI ; 
 int BT848_INT_SCERR ; 
 int /*<<< orphan*/  BT848_INT_STAT ; 
 TYPE_2__* bttv_tvcards ; 
 int /*<<< orphan*/  btwrite (int,int /*<<< orphan*/ ) ; 
 scalar_t__ fdsr ; 

__attribute__((used)) static void init_irqreg(struct bttv *btv)
{
	/* clear status */
	btwrite(0xfffffUL, BT848_INT_STAT);

	if (bttv_tvcards[btv->c.type].no_video) {
		/* i2c only */
		btwrite(BT848_INT_I2CDONE,
			BT848_INT_MASK);
	} else {
		/* full video */
		btwrite((btv->triton1)  |
			(btv->gpioirq ? BT848_INT_GPINT : 0) |
			BT848_INT_SCERR |
			(fdsr ? BT848_INT_FDSR : 0) |
			BT848_INT_RISCI | BT848_INT_OCERR |
			BT848_INT_FMTCHG|BT848_INT_HLOCK|
			BT848_INT_I2CDONE,
			BT848_INT_MASK);
	}
}