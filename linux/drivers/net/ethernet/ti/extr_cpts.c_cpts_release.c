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
struct cpts {int /*<<< orphan*/  refclk; } ;

/* Variables and functions */
 scalar_t__ WARN_ON (int) ; 
 int /*<<< orphan*/  clk_unprepare (int /*<<< orphan*/ ) ; 

void cpts_release(struct cpts *cpts)
{
	if (!cpts)
		return;

	if (WARN_ON(!cpts->refclk))
		return;

	clk_unprepare(cpts->refclk);
}