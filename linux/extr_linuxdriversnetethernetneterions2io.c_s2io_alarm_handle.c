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
struct s2io_nic {int /*<<< orphan*/  alarm_timer; struct net_device* dev; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 int HZ ; 
 int /*<<< orphan*/  alarm_timer ; 
 struct s2io_nic* from_timer (int /*<<< orphan*/ ,struct timer_list*,int /*<<< orphan*/ ) ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  mod_timer (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  s2io_handle_errors (struct net_device*) ; 
 struct s2io_nic* sp ; 

__attribute__((used)) static void
s2io_alarm_handle(struct timer_list *t)
{
	struct s2io_nic *sp = from_timer(sp, t, alarm_timer);
	struct net_device *dev = sp->dev;

	s2io_handle_errors(dev);
	mod_timer(&sp->alarm_timer, jiffies + HZ / 2);
}