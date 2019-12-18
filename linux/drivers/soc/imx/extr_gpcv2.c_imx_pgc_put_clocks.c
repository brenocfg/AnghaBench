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
struct imx_pgc_domain {int num_clks; int /*<<< orphan*/ * clk; } ;

/* Variables and functions */
 int /*<<< orphan*/  clk_put (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void imx_pgc_put_clocks(struct imx_pgc_domain *domain)
{
	int i;

	for (i = domain->num_clks - 1; i >= 0; i--)
		clk_put(domain->clk[i]);
}