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

/* Variables and functions */
 scalar_t__ LOAD_FREQ ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  mod_timer (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  spu_calc_load () ; 
 int /*<<< orphan*/  spuloadavg_timer ; 

__attribute__((used)) static void spuloadavg_wake(struct timer_list *unused)
{
	mod_timer(&spuloadavg_timer, jiffies + LOAD_FREQ);
	spu_calc_load();
}