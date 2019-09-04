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
struct clk_core {unsigned long rate; int /*<<< orphan*/  parent; int /*<<< orphan*/  num_parents; } ;

/* Variables and functions */

__attribute__((used)) static unsigned long clk_core_get_rate_nolock(struct clk_core *core)
{
	unsigned long ret;

	if (!core) {
		ret = 0;
		goto out;
	}

	ret = core->rate;

	if (!core->num_parents)
		goto out;

	if (!core->parent)
		ret = 0;

out:
	return ret;
}