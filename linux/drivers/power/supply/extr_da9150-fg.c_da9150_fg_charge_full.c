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
struct da9150_fg {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DA9150_QIF_FCC_MAH ; 
 int /*<<< orphan*/  DA9150_QIF_FCC_MAH_SIZE ; 
 int da9150_fg_read_attr_sync (struct da9150_fg*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int da9150_fg_charge_full(struct da9150_fg *fg,
				 union power_supply_propval *val)
{
	val->intval = da9150_fg_read_attr_sync(fg, DA9150_QIF_FCC_MAH,
					       DA9150_QIF_FCC_MAH_SIZE);

	val->intval = val->intval * 1000;

	return 0;
}