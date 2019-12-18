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
struct clk {int enable_bit; } ;

/* Variables and functions */
 int sh_clk_read (struct clk*) ; 
 int /*<<< orphan*/  sh_clk_write (int,struct clk*) ; 

__attribute__((used)) static void sh_clk_mstp_disable(struct clk *clk)
{
	sh_clk_write(sh_clk_read(clk) | (1 << clk->enable_bit), clk);
}