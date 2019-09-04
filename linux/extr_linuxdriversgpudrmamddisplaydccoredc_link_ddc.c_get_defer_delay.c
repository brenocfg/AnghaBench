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
typedef  int /*<<< orphan*/  uint32_t ;
struct ddc_service {int transaction_type; int /*<<< orphan*/  dongle_type; } ;

/* Variables and functions */
#define  DDC_TRANSACTION_TYPE_I2C_OVER_AUX 129 
#define  DDC_TRANSACTION_TYPE_I2C_OVER_AUX_WITH_DEFER 128 
 int /*<<< orphan*/  DISPLAY_DONGLE_DP_DVI_CONVERTER ; 
 int /*<<< orphan*/  DISPLAY_DONGLE_DP_HDMI_CONVERTER ; 
 int /*<<< orphan*/  DISPLAY_DONGLE_DP_VGA_CONVERTER ; 
 int /*<<< orphan*/  DP_TRANSLATOR_DELAY ; 
 int /*<<< orphan*/  defer_delay_converter_wa (struct ddc_service*,int /*<<< orphan*/ ) ; 

uint32_t get_defer_delay(struct ddc_service *ddc)
{
	uint32_t defer_delay = 0;

	switch (ddc->transaction_type) {
	case DDC_TRANSACTION_TYPE_I2C_OVER_AUX:
		if ((DISPLAY_DONGLE_DP_VGA_CONVERTER == ddc->dongle_type) ||
			(DISPLAY_DONGLE_DP_DVI_CONVERTER == ddc->dongle_type) ||
			(DISPLAY_DONGLE_DP_HDMI_CONVERTER ==
				ddc->dongle_type)) {

			defer_delay = DP_TRANSLATOR_DELAY;

			defer_delay =
				defer_delay_converter_wa(ddc, defer_delay);

		} else /*sink has a delay different from an Active Converter*/
			defer_delay = 0;
		break;
	case DDC_TRANSACTION_TYPE_I2C_OVER_AUX_WITH_DEFER:
		defer_delay = DP_TRANSLATOR_DELAY;
		break;
	default:
		break;
	}
	return defer_delay;
}