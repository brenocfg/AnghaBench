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
struct device_node {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iproc_pll_clk_setup (struct device_node*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sr_genpll3 ; 
 int /*<<< orphan*/  sr_genpll3_clk ; 

__attribute__((used)) static void sr_genpll3_clk_init(struct device_node *node)
{
	iproc_pll_clk_setup(node, &sr_genpll3, NULL, 0, sr_genpll3_clk,
			    ARRAY_SIZE(sr_genpll3_clk));
}