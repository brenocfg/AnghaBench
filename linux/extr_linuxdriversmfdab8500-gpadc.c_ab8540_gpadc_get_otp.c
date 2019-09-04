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
typedef  int /*<<< orphan*/  u16 ;
struct ab8500_gpadc {TYPE_1__* cal_data; } ;
struct TYPE_2__ {int /*<<< orphan*/  otp_calib_hi; int /*<<< orphan*/  otp_calib_lo; } ;

/* Variables and functions */
 size_t ADC_INPUT_BTEMP ; 
 size_t ADC_INPUT_IBAT ; 
 size_t ADC_INPUT_VBAT ; 
 size_t ADC_INPUT_VMAIN ; 

void ab8540_gpadc_get_otp(struct ab8500_gpadc *gpadc,
			u16 *vmain_l, u16 *vmain_h, u16 *btemp_l, u16 *btemp_h,
			u16 *vbat_l, u16 *vbat_h, u16 *ibat_l, u16 *ibat_h)
{
	*vmain_l = gpadc->cal_data[ADC_INPUT_VMAIN].otp_calib_lo;
	*vmain_h = gpadc->cal_data[ADC_INPUT_VMAIN].otp_calib_hi;
	*btemp_l = gpadc->cal_data[ADC_INPUT_BTEMP].otp_calib_lo;
	*btemp_h = gpadc->cal_data[ADC_INPUT_BTEMP].otp_calib_hi;
	*vbat_l  = gpadc->cal_data[ADC_INPUT_VBAT].otp_calib_lo;
	*vbat_h  = gpadc->cal_data[ADC_INPUT_VBAT].otp_calib_hi;
	*ibat_l  = gpadc->cal_data[ADC_INPUT_IBAT].otp_calib_lo;
	*ibat_h  = gpadc->cal_data[ADC_INPUT_IBAT].otp_calib_hi;
}