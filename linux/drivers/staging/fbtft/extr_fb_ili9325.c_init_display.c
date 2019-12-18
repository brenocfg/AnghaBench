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
struct TYPE_4__ {scalar_t__ cs; } ;
struct TYPE_3__ {int /*<<< orphan*/  (* reset ) (struct fbtft_par*) ;} ;
struct fbtft_par {TYPE_2__ gpio; TYPE_1__ fbtftops; } ;

/* Variables and functions */
 int BIT (int) ; 
 int bt ; 
 int /*<<< orphan*/  gpiod_set_value (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mdelay (int) ; 
 int /*<<< orphan*/  stub1 (struct fbtft_par*) ; 
 int vc ; 
 int vcm ; 
 int vdv ; 
 int vrh ; 
 int /*<<< orphan*/  write_reg (struct fbtft_par*,int,int) ; 

__attribute__((used)) static int init_display(struct fbtft_par *par)
{
	par->fbtftops.reset(par);

	if (par->gpio.cs)
		gpiod_set_value(par->gpio.cs, 0);  /* Activate chip */

	bt &= 0x07;
	vc &= 0x07;
	vrh &= 0x0f;
	vdv &= 0x1f;
	vcm &= 0x3f;

	/* Initialization sequence from ILI9325 Application Notes */

	/* ----------- Start Initial Sequence ----------- */
	write_reg(par, 0x00E3, 0x3008); /* Set internal timing */
	write_reg(par, 0x00E7, 0x0012); /* Set internal timing */
	write_reg(par, 0x00EF, 0x1231); /* Set internal timing */
	write_reg(par, 0x0001, 0x0100); /* set SS and SM bit */
	write_reg(par, 0x0002, 0x0700); /* set 1 line inversion */
	write_reg(par, 0x0004, 0x0000); /* Resize register */
	write_reg(par, 0x0008, 0x0207); /* set the back porch and front porch */
	write_reg(par, 0x0009, 0x0000); /* set non-display area refresh cycle */
	write_reg(par, 0x000A, 0x0000); /* FMARK function */
	write_reg(par, 0x000C, 0x0000); /* RGB interface setting */
	write_reg(par, 0x000D, 0x0000); /* Frame marker Position */
	write_reg(par, 0x000F, 0x0000); /* RGB interface polarity */

	/* ----------- Power On sequence ----------- */
	write_reg(par, 0x0010, 0x0000); /* SAP, BT[3:0], AP, DSTB, SLP, STB */
	write_reg(par, 0x0011, 0x0007); /* DC1[2:0], DC0[2:0], VC[2:0] */
	write_reg(par, 0x0012, 0x0000); /* VREG1OUT voltage */
	write_reg(par, 0x0013, 0x0000); /* VDV[4:0] for VCOM amplitude */
	mdelay(200); /* Dis-charge capacitor power voltage */
	write_reg(par, 0x0010, /* SAP, BT[3:0], AP, DSTB, SLP, STB */
		BIT(12) | (bt << 8) | BIT(7) | BIT(4));
	write_reg(par, 0x0011, 0x220 | vc); /* DC1[2:0], DC0[2:0], VC[2:0] */
	mdelay(50); /* Delay 50ms */
	write_reg(par, 0x0012, vrh); /* Internal reference voltage= Vci; */
	mdelay(50); /* Delay 50ms */
	write_reg(par, 0x0013, vdv << 8); /* Set VDV[4:0] for VCOM amplitude */
	write_reg(par, 0x0029, vcm); /* Set VCM[5:0] for VCOMH */
	write_reg(par, 0x002B, 0x000C); /* Set Frame Rate */
	mdelay(50); /* Delay 50ms */
	write_reg(par, 0x0020, 0x0000); /* GRAM horizontal Address */
	write_reg(par, 0x0021, 0x0000); /* GRAM Vertical Address */

	/*------------------ Set GRAM area --------------- */
	write_reg(par, 0x0050, 0x0000); /* Horizontal GRAM Start Address */
	write_reg(par, 0x0051, 0x00EF); /* Horizontal GRAM End Address */
	write_reg(par, 0x0052, 0x0000); /* Vertical GRAM Start Address */
	write_reg(par, 0x0053, 0x013F); /* Vertical GRAM Start Address */
	write_reg(par, 0x0060, 0xA700); /* Gate Scan Line */
	write_reg(par, 0x0061, 0x0001); /* NDL,VLE, REV */
	write_reg(par, 0x006A, 0x0000); /* set scrolling line */

	/*-------------- Partial Display Control --------- */
	write_reg(par, 0x0080, 0x0000);
	write_reg(par, 0x0081, 0x0000);
	write_reg(par, 0x0082, 0x0000);
	write_reg(par, 0x0083, 0x0000);
	write_reg(par, 0x0084, 0x0000);
	write_reg(par, 0x0085, 0x0000);

	/*-------------- Panel Control ------------------- */
	write_reg(par, 0x0090, 0x0010);
	write_reg(par, 0x0092, 0x0600);
	write_reg(par, 0x0007, 0x0133); /* 262K color and display ON */

	return 0;
}