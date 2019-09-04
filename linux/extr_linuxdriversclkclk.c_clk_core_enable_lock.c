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
struct clk_core {int dummy; } ;

/* Variables and functions */
 int clk_core_enable (struct clk_core*) ; 
 unsigned long clk_enable_lock () ; 
 int /*<<< orphan*/  clk_enable_unlock (unsigned long) ; 

__attribute__((used)) static int clk_core_enable_lock(struct clk_core *core)
{
	unsigned long flags;
	int ret;

	flags = clk_enable_lock();
	ret = clk_core_enable(core);
	clk_enable_unlock(flags);

	return ret;
}