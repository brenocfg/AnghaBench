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
struct abx500_res_to_temp {int resist; int temp; } ;
struct ab8500_gpadc_cfg {int tbl_sz; int vcc; int r_up; struct abx500_res_to_temp* temp_tbl; } ;

/* Variables and functions */
 int EINVAL ; 

__attribute__((used)) static int ab8500_voltage_to_temp(struct ab8500_gpadc_cfg *cfg,
		int v_ntc, int *temp)
{
	int r_ntc, i = 0, tbl_sz = cfg->tbl_sz;
	const struct abx500_res_to_temp *tbl = cfg->temp_tbl;

	if (cfg->vcc < 0 || v_ntc >= cfg->vcc)
		return -EINVAL;

	r_ntc = v_ntc * cfg->r_up / (cfg->vcc - v_ntc);
	if (r_ntc > tbl[0].resist || r_ntc < tbl[tbl_sz - 1].resist)
		return -EINVAL;

	while (!(r_ntc <= tbl[i].resist && r_ntc > tbl[i + 1].resist) &&
			i < tbl_sz - 2)
		i++;

	/* return milli-Celsius */
	*temp = tbl[i].temp * 1000 + ((tbl[i + 1].temp - tbl[i].temp) * 1000 *
		(r_ntc - tbl[i].resist)) / (tbl[i + 1].resist - tbl[i].resist);

	return 0;
}