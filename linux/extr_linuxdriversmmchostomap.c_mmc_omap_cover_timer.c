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
struct timer_list {int dummy; } ;
struct mmc_omap_slot {int /*<<< orphan*/  cover_tasklet; } ;

/* Variables and functions */
 int /*<<< orphan*/  cover_timer ; 
 struct mmc_omap_slot* from_timer (int /*<<< orphan*/ ,struct timer_list*,int /*<<< orphan*/ ) ; 
 struct mmc_omap_slot* slot ; 
 int /*<<< orphan*/  tasklet_schedule (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void mmc_omap_cover_timer(struct timer_list *t)
{
	struct mmc_omap_slot *slot = from_timer(slot, t, cover_timer);
	tasklet_schedule(&slot->cover_tasklet);
}