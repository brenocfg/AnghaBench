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
struct sci_clk_provider {int num_clocks; int /*<<< orphan*/ * clocks; } ;

/* Variables and functions */
 int _sci_clk_build (struct sci_clk_provider*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ti_sci_init_clocks(struct sci_clk_provider *p)
{
	int i;
	int ret;

	for (i = 0; i < p->num_clocks; i++) {
		ret = _sci_clk_build(p, p->clocks[i]);
		if (ret)
			return ret;
	}

	return 0;
}