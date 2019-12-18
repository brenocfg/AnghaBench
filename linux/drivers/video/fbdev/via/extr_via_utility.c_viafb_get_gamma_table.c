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
typedef  int u32 ;
typedef  int u16 ;
struct TYPE_4__ {TYPE_1__* chip_info; } ;
struct TYPE_3__ {int gfx_chip_name; } ;

/* Variables and functions */
 int /*<<< orphan*/  BIT0 ; 
 int /*<<< orphan*/  BIT7 ; 
 int /*<<< orphan*/  CR33 ; 
 int /*<<< orphan*/  LUT_DATA ; 
 int /*<<< orphan*/  LUT_INDEX_READ ; 
 int /*<<< orphan*/  SR16 ; 
 int /*<<< orphan*/  SR1A ; 
#define  UNICHROME_CLE266 136 
#define  UNICHROME_CN700 135 
#define  UNICHROME_CX700 134 
#define  UNICHROME_K400 133 
#define  UNICHROME_K800 132 
#define  UNICHROME_K8M890 131 
#define  UNICHROME_P4M890 130 
#define  UNICHROME_P4M900 129 
#define  UNICHROME_PM800 128 
 int /*<<< orphan*/  VIACR ; 
 int /*<<< orphan*/  VIASR ; 
 unsigned char inb (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  outb (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 unsigned char viafb_read_reg (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  viafb_write_reg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned char) ; 
 int /*<<< orphan*/  viafb_write_reg_mask (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 TYPE_2__* viaparinfo ; 

void viafb_get_gamma_table(unsigned int *gamma_table)
{
	unsigned char color_r, color_g, color_b;
	unsigned char sr1a = 0;
	int i;

	/* Enable Gamma */
	switch (viaparinfo->chip_info->gfx_chip_name) {
	case UNICHROME_CLE266:
	case UNICHROME_K400:
		viafb_write_reg_mask(SR16, VIASR, 0x80, BIT7);
		break;

	case UNICHROME_K800:
	case UNICHROME_PM800:
	case UNICHROME_CN700:
	case UNICHROME_CX700:
	case UNICHROME_K8M890:
	case UNICHROME_P4M890:
	case UNICHROME_P4M900:
		viafb_write_reg_mask(CR33, VIACR, 0x80, BIT7);
		break;
	}
	sr1a = viafb_read_reg(VIASR, SR1A);
	viafb_write_reg_mask(SR1A, VIASR, 0x0, BIT0);

	/* Reading gamma table to get color value */
	outb(0, LUT_INDEX_READ);
	for (i = 0; i < 256; i++) {
		color_r = inb(LUT_DATA);
		color_g = inb(LUT_DATA);
		color_b = inb(LUT_DATA);
		gamma_table[i] =
		    ((((u32) color_r) << 16) |
		     (((u16) color_g) << 8)) | color_b;
	}
	viafb_write_reg(SR1A, VIASR, sr1a);
}