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
struct at86rf230_local {int /*<<< orphan*/  slp_tr; } ;

/* Variables and functions */
 int /*<<< orphan*/  gpio_set_value (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static inline void
at86rf230_slp_tr_rising_edge(struct at86rf230_local *lp)
{
	gpio_set_value(lp->slp_tr, 1);
	udelay(1);
	gpio_set_value(lp->slp_tr, 0);
}