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
struct TYPE_6__ {TYPE_2__* lvds_setting_info; TYPE_1__* lvds_setting_info2; } ;
struct TYPE_5__ {scalar_t__ device_lcd_dualedge; } ;
struct TYPE_4__ {scalar_t__ device_lcd_dualedge; } ;

/* Variables and functions */
 scalar_t__ BIT4 ; 
 scalar_t__ BIT5 ; 
 int /*<<< orphan*/  CRD2 ; 
 int /*<<< orphan*/  VIACR ; 
 scalar_t__ viafb_DVI_ON ; 
 scalar_t__ viafb_LCD2_ON ; 
 scalar_t__ viafb_LCD_ON ; 
 int /*<<< orphan*/  viafb_write_reg_mask (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,scalar_t__) ; 
 TYPE_3__* viaparinfo ; 

__attribute__((used)) static void set_display_channel(void)
{
	/*If viafb_LCD2_ON, on cx700, internal lvds's information
	is keeped on lvds_setting_info2 */
	if (viafb_LCD2_ON &&
		viaparinfo->lvds_setting_info2->device_lcd_dualedge) {
		/* For dual channel LCD: */
		/* Set to Dual LVDS channel. */
		viafb_write_reg_mask(CRD2, VIACR, 0x20, BIT4 + BIT5);
	} else if (viafb_LCD_ON && viafb_DVI_ON) {
		/* For LCD+DFP: */
		/* Set to LVDS1 + TMDS channel. */
		viafb_write_reg_mask(CRD2, VIACR, 0x10, BIT4 + BIT5);
	} else if (viafb_DVI_ON) {
		/* Set to single TMDS channel. */
		viafb_write_reg_mask(CRD2, VIACR, 0x30, BIT4 + BIT5);
	} else if (viafb_LCD_ON) {
		if (viaparinfo->lvds_setting_info->device_lcd_dualedge) {
			/* For dual channel LCD: */
			/* Set to Dual LVDS channel. */
			viafb_write_reg_mask(CRD2, VIACR, 0x20, BIT4 + BIT5);
		} else {
			/* Set to LVDS0 + LVDS1 channel. */
			viafb_write_reg_mask(CRD2, VIACR, 0x00, BIT4 + BIT5);
		}
	}
}