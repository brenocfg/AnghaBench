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
typedef  unsigned int u64 ;
typedef  unsigned int u32 ;
struct ntc_thermistor_platform_data {unsigned int pullup_uv; unsigned int pullup_ohm; unsigned int pulldown_ohm; scalar_t__ connect; } ;
struct ntc_data {struct ntc_thermistor_platform_data* pdata; } ;

/* Variables and functions */
 int INT_MAX ; 
 scalar_t__ NTC_CONNECTED_GROUND ; 
 scalar_t__ NTC_CONNECTED_POSITIVE ; 
 unsigned int div64_u64_safe (unsigned int,unsigned int) ; 
 unsigned int div_u64 (unsigned int,unsigned int) ; 

__attribute__((used)) static int get_ohm_of_thermistor(struct ntc_data *data, unsigned int uv)
{
	struct ntc_thermistor_platform_data *pdata = data->pdata;
	u32 puv = pdata->pullup_uv;
	u64 n, puo, pdo;
	puo = pdata->pullup_ohm;
	pdo = pdata->pulldown_ohm;

	if (uv == 0)
		return (pdata->connect == NTC_CONNECTED_POSITIVE) ?
			INT_MAX : 0;
	if (uv >= puv)
		return (pdata->connect == NTC_CONNECTED_POSITIVE) ?
			0 : INT_MAX;

	if (pdata->connect == NTC_CONNECTED_POSITIVE && puo == 0)
		n = div_u64(pdo * (puv - uv), uv);
	else if (pdata->connect == NTC_CONNECTED_GROUND && pdo == 0)
		n = div_u64(puo * uv, puv - uv);
	else if (pdata->connect == NTC_CONNECTED_POSITIVE)
		n = div64_u64_safe(pdo * puo * (puv - uv),
				puo * uv - pdo * (puv - uv));
	else
		n = div64_u64_safe(pdo * puo * uv, pdo * (puv - uv) - puo * uv);

	if (n > INT_MAX)
		n = INT_MAX;
	return n;
}