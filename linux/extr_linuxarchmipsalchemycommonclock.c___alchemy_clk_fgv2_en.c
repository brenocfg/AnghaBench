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
struct alchemy_fgcs_clk {int shift; int parent; int isen; int /*<<< orphan*/  reg; } ;

/* Variables and functions */
 unsigned long alchemy_rdsys (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  alchemy_wrsys (unsigned long,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void __alchemy_clk_fgv2_en(struct alchemy_fgcs_clk *c)
{
	unsigned long v = alchemy_rdsys(c->reg);

	v &= ~(3 << c->shift);
	v |= (c->parent & 3) << c->shift;
	alchemy_wrsys(v, c->reg);
	c->isen = 1;
}