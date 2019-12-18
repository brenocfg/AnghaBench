#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct tp_params {int dummy; } ;
struct petp {TYPE_1__* adapter; } ;
struct TYPE_3__ {scalar_t__ regs; } ;
typedef  TYPE_1__ adapter_t ;

/* Variables and functions */
 scalar_t__ A_TP_RESET ; 
 int /*<<< orphan*/  F_TP_RESET ; 
 int /*<<< orphan*/  tp_init (TYPE_1__*,struct tp_params*,unsigned int) ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,scalar_t__) ; 

int t1_tp_reset(struct petp *tp, struct tp_params *p, unsigned int tp_clk)
{
	adapter_t *adapter = tp->adapter;

	tp_init(adapter, p, tp_clk);
	writel(F_TP_RESET, adapter->regs +  A_TP_RESET);
	return 0;
}