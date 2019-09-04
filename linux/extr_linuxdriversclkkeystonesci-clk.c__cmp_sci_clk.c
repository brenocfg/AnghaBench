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
struct sci_clk {scalar_t__ dev_id; scalar_t__ clk_id; } ;

/* Variables and functions */

__attribute__((used)) static int _cmp_sci_clk(const void *a, const void *b)
{
	const struct sci_clk *ca = a;
	const struct sci_clk *cb = *(struct sci_clk **)b;

	if (ca->dev_id == cb->dev_id && ca->clk_id == cb->clk_id)
		return 0;
	if (ca->dev_id > cb->dev_id ||
	    (ca->dev_id == cb->dev_id && ca->clk_id > cb->clk_id))
		return 1;
	return -1;
}