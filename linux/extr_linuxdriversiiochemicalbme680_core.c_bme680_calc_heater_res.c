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
typedef  int u8 ;
typedef  int u16 ;
struct bme680_calib {int par_gh3; int par_gh1; int par_gh2; int res_heat_range; int res_heat_val; } ;
struct bme680_data {struct bme680_calib bme680; } ;
typedef  int s32 ;

/* Variables and functions */
 scalar_t__ BME680_AMB_TEMP ; 

__attribute__((used)) static u8 bme680_calc_heater_res(struct bme680_data *data, u16 temp)
{
	struct bme680_calib *calib = &data->bme680;
	s32 var1, var2, var3, var4, var5, heatr_res_x100;
	u8 heatr_res;

	if (temp > 400) /* Cap temperature */
		temp = 400;

	var1 = (((s32) BME680_AMB_TEMP * calib->par_gh3) / 1000) * 256;
	var2 = (calib->par_gh1 + 784) * (((((calib->par_gh2 + 154009) *
						temp * 5) / 100)
						+ 3276800) / 10);
	var3 = var1 + (var2 / 2);
	var4 = (var3 / (calib->res_heat_range + 4));
	var5 = 131 * calib->res_heat_val + 65536;
	heatr_res_x100 = ((var4 / var5) - 250) * 34;
	heatr_res = (heatr_res_x100 + 50) / 100;

	return heatr_res;
}