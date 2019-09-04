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
struct cht_wc_extcon_data {int dummy; } ;

/* Variables and functions */
 int CHT_WC_PWRSRC_ID_FLOAT ; 
 int CHT_WC_PWRSRC_ID_GND ; 
 int USB_ID_FLOAT ; 
 int USB_ID_GND ; 

__attribute__((used)) static int cht_wc_extcon_get_id(struct cht_wc_extcon_data *ext, int pwrsrc_sts)
{
	if (pwrsrc_sts & CHT_WC_PWRSRC_ID_GND)
		return USB_ID_GND;
	if (pwrsrc_sts & CHT_WC_PWRSRC_ID_FLOAT)
		return USB_ID_FLOAT;

	/*
	 * Once we have iio support for the gpadc we should read the USBID
	 * gpadc channel here and determine ACA role based on that.
	 */
	return USB_ID_FLOAT;
}