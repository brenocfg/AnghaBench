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
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  mod_timer (struct timer_list*,scalar_t__) ; 
 int /*<<< orphan*/  timer_setup (struct timer_list*,void (*) (struct timer_list*),int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline
void vxge_os_timer(struct timer_list *timer, void (*func)(struct timer_list *),
		   unsigned long timeout)
{
	timer_setup(timer, func, 0);
	mod_timer(timer, jiffies + timeout);
}