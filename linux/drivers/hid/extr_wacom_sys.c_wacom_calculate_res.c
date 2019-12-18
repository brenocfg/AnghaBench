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
struct wacom_features {int unit; int unitExpo; int /*<<< orphan*/  y_phy; int /*<<< orphan*/  y_max; void* y_resolution; int /*<<< orphan*/  x_phy; int /*<<< orphan*/  x_max; void* x_resolution; } ;

/* Variables and functions */
 void* wacom_calc_hid_res (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static void wacom_calculate_res(struct wacom_features *features)
{
	/* set unit to "100th of a mm" for devices not reported by HID */
	if (!features->unit) {
		features->unit = 0x11;
		features->unitExpo = -3;
	}

	features->x_resolution = wacom_calc_hid_res(features->x_max,
						    features->x_phy,
						    features->unit,
						    features->unitExpo);
	features->y_resolution = wacom_calc_hid_res(features->y_max,
						    features->y_phy,
						    features->unit,
						    features->unitExpo);
}