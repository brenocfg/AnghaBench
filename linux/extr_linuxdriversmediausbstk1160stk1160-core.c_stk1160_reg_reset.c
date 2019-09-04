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
struct stk1160 {int dummy; } ;
struct regval {int const member_0; int member_1; int reg; int /*<<< orphan*/  val; } ;

/* Variables and functions */
#define  STK1160_GCTRL 133 
#define  STK1160_PLLFD 132 
#define  STK1160_PLLSO 131 
#define  STK1160_RMCTL 130 
#define  STK1160_TICTL 129 
#define  STK1160_TIGEN 128 
 int /*<<< orphan*/  stk1160_write_reg (struct stk1160*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void stk1160_reg_reset(struct stk1160 *dev)
{
	int i;

	static const struct regval ctl[] = {
		{STK1160_GCTRL+2, 0x0078},

		{STK1160_RMCTL+1, 0x0000},
		{STK1160_RMCTL+3, 0x0002},

		{STK1160_PLLSO,   0x0010},
		{STK1160_PLLSO+1, 0x0000},
		{STK1160_PLLSO+2, 0x0014},
		{STK1160_PLLSO+3, 0x000E},

		{STK1160_PLLFD,   0x0046},

		/* Timing generator setup */
		{STK1160_TIGEN,   0x0012},
		{STK1160_TICTL,   0x002D},
		{STK1160_TICTL+1, 0x0001},
		{STK1160_TICTL+2, 0x0000},
		{STK1160_TICTL+3, 0x0000},
		{STK1160_TIGEN,   0x0080},

		{0xffff, 0xffff}
	};

	for (i = 0; ctl[i].reg != 0xffff; i++)
		stk1160_write_reg(dev, ctl[i].reg, ctl[i].val);
}