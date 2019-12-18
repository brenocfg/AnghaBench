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
typedef  int /*<<< orphan*/  u8 ;
struct regmap {int dummy; } ;

/* Variables and functions */
 int EPERM ; 
 int /*<<< orphan*/  regcache_cache_bypass (struct regmap*,int) ; 
 struct regmap* twl_get_regmap (int /*<<< orphan*/ ) ; 

int twl_set_regcache_bypass(u8 mod_no, bool enable)
{
	struct regmap *regmap = twl_get_regmap(mod_no);

	if (!regmap)
		return -EPERM;

	regcache_cache_bypass(regmap, enable);

	return 0;
}