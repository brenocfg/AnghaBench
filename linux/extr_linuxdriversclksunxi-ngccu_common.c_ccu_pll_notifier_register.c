#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  notifier_call; } ;
struct ccu_pll_nb {TYPE_3__ clk_nb; TYPE_2__* common; } ;
struct TYPE_4__ {int /*<<< orphan*/  clk; } ;
struct TYPE_5__ {TYPE_1__ hw; } ;

/* Variables and functions */
 int /*<<< orphan*/  ccu_pll_notifier_cb ; 
 int clk_notifier_register (int /*<<< orphan*/ ,TYPE_3__*) ; 

int ccu_pll_notifier_register(struct ccu_pll_nb *pll_nb)
{
	pll_nb->clk_nb.notifier_call = ccu_pll_notifier_cb;

	return clk_notifier_register(pll_nb->common->hw.clk,
				     &pll_nb->clk_nb);
}