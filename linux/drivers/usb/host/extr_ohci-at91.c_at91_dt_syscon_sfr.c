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
struct regmap {int dummy; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (struct regmap*) ; 
 struct regmap* syscon_regmap_lookup_by_compatible (char*) ; 

__attribute__((used)) static struct regmap *at91_dt_syscon_sfr(void)
{
	struct regmap *regmap;

	regmap = syscon_regmap_lookup_by_compatible("atmel,sama5d2-sfr");
	if (IS_ERR(regmap)) {
		regmap = syscon_regmap_lookup_by_compatible("microchip,sam9x60-sfr");
		if (IS_ERR(regmap))
			regmap = NULL;
	}

	return regmap;
}