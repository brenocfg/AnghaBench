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
struct lan78xx_net {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  EVENT_STAT_UPDATE ; 
 struct lan78xx_net* dev ; 
 struct lan78xx_net* from_timer (int /*<<< orphan*/ ,struct timer_list*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lan78xx_defer_kevent (struct lan78xx_net*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stat_monitor ; 

__attribute__((used)) static void lan78xx_stat_monitor(struct timer_list *t)
{
	struct lan78xx_net *dev = from_timer(dev, t, stat_monitor);

	lan78xx_defer_kevent(dev, EVENT_STAT_UPDATE);
}