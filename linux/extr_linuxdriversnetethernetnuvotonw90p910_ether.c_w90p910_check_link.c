#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {struct net_device* dev; } ;
struct w90p910_ether {int /*<<< orphan*/  check_timer; TYPE_1__ mii; } ;
struct timer_list {int dummy; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  check_timer ; 
 struct w90p910_ether* ether ; 
 struct w90p910_ether* from_timer (int /*<<< orphan*/ ,struct timer_list*,int /*<<< orphan*/ ) ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  mod_timer (int /*<<< orphan*/ *,scalar_t__) ; 
 scalar_t__ msecs_to_jiffies (int) ; 
 int /*<<< orphan*/  update_linkspeed (struct net_device*) ; 

__attribute__((used)) static void w90p910_check_link(struct timer_list *t)
{
	struct w90p910_ether *ether = from_timer(ether, t, check_timer);
	struct net_device *dev = ether->mii.dev;

	update_linkspeed(dev);
	mod_timer(&ether->check_timer, jiffies + msecs_to_jiffies(1000));
}