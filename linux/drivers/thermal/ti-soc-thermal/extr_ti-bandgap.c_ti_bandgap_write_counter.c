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
typedef  int u32 ;
struct ti_bandgap {int clk_rate; int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  RMW_BITS (struct ti_bandgap*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  bgap_counter ; 
 int /*<<< orphan*/  counter_mask ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void ti_bandgap_write_counter(struct ti_bandgap *bgp, int id,
				     u32 interval)
{
	interval = interval * bgp->clk_rate / 1000;
	spin_lock(&bgp->lock);
	RMW_BITS(bgp, id, bgap_counter, counter_mask, interval);
	spin_unlock(&bgp->lock);
}