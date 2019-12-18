#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct omap_overlay {int /*<<< orphan*/  manager; } ;
struct TYPE_2__ {int stallmode; } ;
struct mgr_priv_data {TYPE_1__ lcd_config; } ;

/* Variables and functions */
 struct mgr_priv_data* get_mgr_priv (int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool ovl_manual_update(struct omap_overlay *ovl)
{
	struct mgr_priv_data *mp = get_mgr_priv(ovl->manager);

	return mp->lcd_config.stallmode;
}