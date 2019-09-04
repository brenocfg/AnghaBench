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
struct clk {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  notifier_call; } ;
struct ccu_mux_nb {TYPE_1__ clk_nb; } ;

/* Variables and functions */
 int /*<<< orphan*/  ccu_mux_notifier_cb ; 
 int clk_notifier_register (struct clk*,TYPE_1__*) ; 

int ccu_mux_notifier_register(struct clk *clk, struct ccu_mux_nb *mux_nb)
{
	mux_nb->clk_nb.notifier_call = ccu_mux_notifier_cb;

	return clk_notifier_register(clk, &mux_nb->clk_nb);
}