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
union power_supply_propval {int intval; } ;
typedef  int u64 ;
typedef  unsigned long long u32 ;
struct da9150_fg {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DA9150_QIF_IAVG ; 
 int /*<<< orphan*/  DA9150_QIF_IAVG_SIZE ; 
 int /*<<< orphan*/  DA9150_QIF_SD_GAIN ; 
 int /*<<< orphan*/  DA9150_QIF_SD_GAIN_SIZE ; 
 int /*<<< orphan*/  DA9150_QIF_SHUNT_VAL ; 
 int /*<<< orphan*/  DA9150_QIF_SHUNT_VAL_SIZE ; 
 unsigned long long da9150_fg_read_attr (struct da9150_fg*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  da9150_fg_read_sync_end (struct da9150_fg*) ; 
 int /*<<< orphan*/  da9150_fg_read_sync_start (struct da9150_fg*) ; 
 int /*<<< orphan*/  do_div (int,int) ; 

__attribute__((used)) static int da9150_fg_current_avg(struct da9150_fg *fg,
				 union power_supply_propval *val)
{
	u32 iavg, sd_gain, shunt_val;
	u64 div, res;

	da9150_fg_read_sync_start(fg);
	iavg = da9150_fg_read_attr(fg, DA9150_QIF_IAVG,
				   DA9150_QIF_IAVG_SIZE);
	shunt_val = da9150_fg_read_attr(fg, DA9150_QIF_SHUNT_VAL,
					DA9150_QIF_SHUNT_VAL_SIZE);
	sd_gain = da9150_fg_read_attr(fg, DA9150_QIF_SD_GAIN,
				      DA9150_QIF_SD_GAIN_SIZE);
	da9150_fg_read_sync_end(fg);

	div = (u64) (sd_gain * shunt_val * 65536ULL);
	do_div(div, 1000000);
	res = (u64) (iavg * 1000000ULL);
	do_div(res, div);

	val->intval = (int) res;

	return 0;
}