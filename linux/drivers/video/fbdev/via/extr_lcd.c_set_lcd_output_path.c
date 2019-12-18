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
struct TYPE_4__ {TYPE_1__* chip_info; } ;
struct TYPE_3__ {int /*<<< orphan*/  gfx_chip_name; } ;

/* Variables and functions */
 scalar_t__ BIT0 ; 
 scalar_t__ BIT1 ; 
 scalar_t__ BIT2 ; 
 scalar_t__ BIT7 ; 
 int /*<<< orphan*/  CR91 ; 
 int /*<<< orphan*/  CR97 ; 
 int IGA2 ; 
#define  INTERFACE_DFP 132 
#define  INTERFACE_DFP_HIGH 131 
#define  INTERFACE_DFP_LOW 130 
#define  INTERFACE_DVP0 129 
#define  INTERFACE_DVP1 128 
 int /*<<< orphan*/  UNICHROME_K8M890 ; 
 int /*<<< orphan*/  UNICHROME_P4M890 ; 
 int /*<<< orphan*/  VIACR ; 
 int /*<<< orphan*/  viafb_write_reg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  viafb_write_reg_mask (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,scalar_t__) ; 
 TYPE_2__* viaparinfo ; 

__attribute__((used)) static void set_lcd_output_path(int set_iga, int output_interface)
{
	switch (output_interface) {
	case INTERFACE_DFP:
		if ((UNICHROME_K8M890 == viaparinfo->chip_info->gfx_chip_name)
		    || (UNICHROME_P4M890 ==
		    viaparinfo->chip_info->gfx_chip_name))
			viafb_write_reg_mask(CR97, VIACR, 0x84,
				       BIT7 + BIT2 + BIT1 + BIT0);
		/* fall through */
	case INTERFACE_DVP0:
	case INTERFACE_DVP1:
	case INTERFACE_DFP_HIGH:
	case INTERFACE_DFP_LOW:
		if (set_iga == IGA2)
			viafb_write_reg(CR91, VIACR, 0x00);
		break;
	}
}