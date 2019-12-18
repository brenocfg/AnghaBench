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
struct cpts {int /*<<< orphan*/  refclk; int /*<<< orphan*/  txq; int /*<<< orphan*/ * clock; } ;

/* Variables and functions */
 scalar_t__ WARN_ON (int) ; 
 int /*<<< orphan*/  clk_disable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  control ; 
 int /*<<< orphan*/  cpts_write32 (struct cpts*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  int_enable ; 
 int /*<<< orphan*/  ptp_clock_unregister (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  skb_queue_purge (int /*<<< orphan*/ *) ; 

void cpts_unregister(struct cpts *cpts)
{
	if (WARN_ON(!cpts->clock))
		return;

	ptp_clock_unregister(cpts->clock);
	cpts->clock = NULL;

	cpts_write32(cpts, 0, int_enable);
	cpts_write32(cpts, 0, control);

	/* Drop all packet */
	skb_queue_purge(&cpts->txq);

	clk_disable(cpts->refclk);
}