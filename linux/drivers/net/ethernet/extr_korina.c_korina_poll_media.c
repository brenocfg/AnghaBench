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
struct net_device {int dummy; } ;
struct korina_private {int /*<<< orphan*/  media_check_timer; struct net_device* dev; } ;

/* Variables and functions */
 scalar_t__ HZ ; 
 struct korina_private* from_timer (int /*<<< orphan*/ ,struct timer_list*,int /*<<< orphan*/ ) ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  korina_check_media (struct net_device*,int /*<<< orphan*/ ) ; 
 struct korina_private* lp ; 
 int /*<<< orphan*/  media_check_timer ; 
 int /*<<< orphan*/  mod_timer (int /*<<< orphan*/ *,scalar_t__) ; 

__attribute__((used)) static void korina_poll_media(struct timer_list *t)
{
	struct korina_private *lp = from_timer(lp, t, media_check_timer);
	struct net_device *dev = lp->dev;

	korina_check_media(dev, 0);
	mod_timer(&lp->media_check_timer, jiffies + HZ);
}