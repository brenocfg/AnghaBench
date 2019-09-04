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
struct map_info {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  VERSATILE_SYS_FLASH_OFFSET ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 int regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  syscon_regmap ; 

__attribute__((used)) static void versatile_flash_set_vpp(struct map_info *map, int on)
{
	int ret;

	ret = regmap_update_bits(syscon_regmap, VERSATILE_SYS_FLASH_OFFSET,
				 0x01, !!on);
	if (ret)
		pr_err("error setting Versatile VPP\n");
}