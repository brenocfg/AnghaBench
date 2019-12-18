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
struct ieee80211_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  associate_timer ; 
 struct ieee80211_device* dev ; 
 struct ieee80211_device* from_timer (int /*<<< orphan*/ ,struct timer_list*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ieee80211_associate_abort (struct ieee80211_device*) ; 

__attribute__((used)) static void ieee80211_associate_abort_cb(struct timer_list *t)
{
	struct ieee80211_device *dev = from_timer(dev, t, associate_timer);

	ieee80211_associate_abort(dev);
}