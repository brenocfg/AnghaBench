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
typedef  scalar_t__ u8 ;
struct zd_reg_alpha2_map {scalar_t__ reg; char* alpha2; } ;

/* Variables and functions */
 unsigned int ARRAY_SIZE (struct zd_reg_alpha2_map*) ; 
 struct zd_reg_alpha2_map* reg_alpha2_map ; 

__attribute__((used)) static int zd_reg2alpha2(u8 regdomain, char *alpha2)
{
	unsigned int i;
	struct zd_reg_alpha2_map *reg_map;
	for (i = 0; i < ARRAY_SIZE(reg_alpha2_map); i++) {
		reg_map = &reg_alpha2_map[i];
		if (regdomain == reg_map->reg) {
			alpha2[0] = reg_map->alpha2[0];
			alpha2[1] = reg_map->alpha2[1];
			return 0;
		}
	}
	return 1;
}