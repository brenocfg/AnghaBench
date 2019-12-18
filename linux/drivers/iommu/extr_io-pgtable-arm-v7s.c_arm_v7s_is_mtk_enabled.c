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
struct io_pgtable_cfg {int quirks; } ;

/* Variables and functions */
 int /*<<< orphan*/  CONFIG_PHYS_ADDR_T_64BIT ; 
 int IO_PGTABLE_QUIRK_ARM_MTK_EXT ; 
 scalar_t__ IS_ENABLED (int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool arm_v7s_is_mtk_enabled(struct io_pgtable_cfg *cfg)
{
	return IS_ENABLED(CONFIG_PHYS_ADDR_T_64BIT) &&
		(cfg->quirks & IO_PGTABLE_QUIRK_ARM_MTK_EXT);
}