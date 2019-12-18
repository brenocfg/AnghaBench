#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct stv6110x_state {int /*<<< orphan*/ * regs; TYPE_1__* config; } ;
struct TYPE_2__ {int clk_div; } ;

/* Variables and functions */
 int /*<<< orphan*/  CTRL2_CO_DIV ; 
 size_t STV6110x_CTRL2 ; 
 int /*<<< orphan*/  STV6110x_SETFIELD (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void stv6110x_setup_divider(struct stv6110x_state *stv6110x)
{
	switch (stv6110x->config->clk_div) {
	default:
	case 1:
		STV6110x_SETFIELD(stv6110x->regs[STV6110x_CTRL2],
				  CTRL2_CO_DIV,
				  0);
		break;
	case 2:
		STV6110x_SETFIELD(stv6110x->regs[STV6110x_CTRL2],
				  CTRL2_CO_DIV,
				  1);
		break;
	case 4:
		STV6110x_SETFIELD(stv6110x->regs[STV6110x_CTRL2],
				  CTRL2_CO_DIV,
				  2);
		break;
	case 8:
	case 0:
		STV6110x_SETFIELD(stv6110x->regs[STV6110x_CTRL2],
				  CTRL2_CO_DIV,
				  3);
		break;
	}
}