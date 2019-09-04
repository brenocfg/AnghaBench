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
 int /*<<< orphan*/  CINTEGRATOR_FLMASK ; 
 int CINTEGRATOR_FLVPPEN ; 
 int CINTEGRATOR_FLWREN ; 
 int /*<<< orphan*/  INTCP_FLASHPROG_OFFSET ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 int regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  syscon_regmap ; 

__attribute__((used)) static void cp_flash_set_vpp(struct map_info *map, int on)
{
	int ret;

	if (on) {
		ret = regmap_update_bits(syscon_regmap,
				INTCP_FLASHPROG_OFFSET,
				CINTEGRATOR_FLMASK,
				CINTEGRATOR_FLVPPEN | CINTEGRATOR_FLWREN);
		if (ret)
			pr_err("error setting CP VPP\n");
	} else {
		ret = regmap_update_bits(syscon_regmap,
				INTCP_FLASHPROG_OFFSET,
				CINTEGRATOR_FLMASK,
				0);
		if (ret)
			pr_err("error setting CP VPP\n");
	}
}