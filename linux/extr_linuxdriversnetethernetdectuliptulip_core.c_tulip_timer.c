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
struct tulip_private {int /*<<< orphan*/  media_work; struct net_device* dev; } ;
struct timer_list {int dummy; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 struct tulip_private* from_timer (int /*<<< orphan*/ ,struct timer_list*,int /*<<< orphan*/ ) ; 
 scalar_t__ netif_running (struct net_device*) ; 
 int /*<<< orphan*/  schedule_work (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  timer ; 
 struct tulip_private* tp ; 

__attribute__((used)) static void tulip_timer(struct timer_list *t)
{
	struct tulip_private *tp = from_timer(tp, t, timer);
	struct net_device *dev = tp->dev;

	if (netif_running(dev))
		schedule_work(&tp->media_work);
}