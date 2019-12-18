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
struct clock_source {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  TO_DCE110_CLK_SRC (struct clock_source*) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 

void dce80_clock_source_destroy(struct clock_source **clk_src)
{
	kfree(TO_DCE110_CLK_SRC(*clk_src));
	*clk_src = NULL;
}