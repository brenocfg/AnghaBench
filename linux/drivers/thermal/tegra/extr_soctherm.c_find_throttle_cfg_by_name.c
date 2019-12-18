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
struct tegra_soctherm {struct soctherm_throt_cfg* throt_cfgs; } ;
struct soctherm_throt_cfg {scalar_t__ name; } ;

/* Variables and functions */
 int /*<<< orphan*/  strcmp (scalar_t__,char const*) ; 

__attribute__((used)) static struct soctherm_throt_cfg *
find_throttle_cfg_by_name(struct tegra_soctherm *ts, const char *name)
{
	unsigned int i;

	for (i = 0; ts->throt_cfgs[i].name; i++)
		if (!strcmp(ts->throt_cfgs[i].name, name))
			return &ts->throt_cfgs[i];

	return NULL;
}