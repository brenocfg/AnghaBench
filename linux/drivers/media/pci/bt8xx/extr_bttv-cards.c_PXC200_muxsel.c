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
struct TYPE_2__ {int /*<<< orphan*/  nr; } ;
struct bttv {scalar_t__ cardid; TYPE_1__ c; } ;

/* Variables and functions */
 int /*<<< orphan*/  BT848_GPIO_DATA ; 
 int /*<<< orphan*/  BT848_GPIO_OUT_EN ; 
 int /*<<< orphan*/  BT848_IFORM ; 
 int /*<<< orphan*/  BT848_IFORM_MUXSEL ; 
 int PX_CFG_PXC200F ; 
 int PX_I2C_PIC ; 
 scalar_t__ PX_PXC200A_CARDID ; 
 int /*<<< orphan*/  btand (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  btaor (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int btread (int /*<<< orphan*/ ) ; 
 int bttv_I2CRead (struct bttv*,int,int /*<<< orphan*/ *) ; 
 int bttv_I2CWrite (struct bttv*,int,unsigned char,unsigned char,int) ; 
 int /*<<< orphan*/  btwrite (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_debug (char*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void PXC200_muxsel(struct bttv *btv, unsigned int input)
{
	int rc;
	long mux;
	int bitmask;
	unsigned char buf[2];

	/* Read PIC config to determine if this is a PXC200F */
	/* PX_I2C_CMD_CFG*/
	buf[0]=0;
	buf[1]=0;
	rc=bttv_I2CWrite(btv,(PX_I2C_PIC<<1),buf[0],buf[1],1);
	if (rc) {
		pr_debug("%d: PXC200_muxsel: pic cfg write failed:%d\n",
			 btv->c.nr, rc);
	  /* not PXC ? do nothing */
		return;
	}

	rc=bttv_I2CRead(btv,(PX_I2C_PIC<<1),NULL);
	if (!(rc & PX_CFG_PXC200F)) {
		pr_debug("%d: PXC200_muxsel: not PXC200F rc:%d\n",
			 btv->c.nr, rc);
		return;
	}


	/* The multiplexer in the 200F is handled by the GPIO port */
	/* get correct mapping between inputs  */
	/*  mux = bttv_tvcards[btv->type].muxsel[input] & 3; */
	/* ** not needed!?   */
	mux = input;

	/* make sure output pins are enabled */
	/* bitmask=0x30f; */
	bitmask=0x302;
	/* check whether we have a PXC200A */
	if (btv->cardid == PX_PXC200A_CARDID)  {
	   bitmask ^= 0x180; /* use 7 and 9, not 8 and 9 */
	   bitmask |= 7<<4; /* the DAC */
	}
	btwrite(bitmask, BT848_GPIO_OUT_EN);

	bitmask = btread(BT848_GPIO_DATA);
	if (btv->cardid == PX_PXC200A_CARDID)
	  bitmask = (bitmask & ~0x280) | ((mux & 2) << 8) | ((mux & 1) << 7);
	else /* older device */
	  bitmask = (bitmask & ~0x300) | ((mux & 3) << 8);
	btwrite(bitmask,BT848_GPIO_DATA);

	/*
	 * Was "to be safe, set the bt848 to input 0"
	 * Actually, since it's ok at load time, better not messing
	 * with these bits (on PXC200AF you need to set mux 2 here)
	 *
	 * needed because bttv-driver sets mux before calling this function
	 */
	if (btv->cardid == PX_PXC200A_CARDID)
	  btaor(2<<5, ~BT848_IFORM_MUXSEL, BT848_IFORM);
	else /* older device */
	  btand(~BT848_IFORM_MUXSEL,BT848_IFORM);

	pr_debug("%d: setting input channel to:%d\n", btv->c.nr, (int)mux);
}