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
struct pic32_sport {int /*<<< orphan*/  ref_clk; int /*<<< orphan*/  clk; } ;

/* Variables and functions */
 int clk_prepare_enable (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline int pic32_enable_clock(struct pic32_sport *sport)
{
	int ret = clk_prepare_enable(sport->clk);

	if (ret)
		return ret;

	sport->ref_clk++;
	return 0;
}