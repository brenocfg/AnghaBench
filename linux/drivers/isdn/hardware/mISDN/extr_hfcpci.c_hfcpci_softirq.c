#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct timer_list {int dummy; } ;
typedef  scalar_t__ s32 ;
struct TYPE_5__ {int /*<<< orphan*/  driver; } ;
struct TYPE_4__ {scalar_t__ expires; } ;

/* Variables and functions */
 int /*<<< orphan*/  WARN_ON_ONCE (int) ; 
 int /*<<< orphan*/  _hfcpci_softirq ; 
 int /*<<< orphan*/  add_timer (TYPE_1__*) ; 
 scalar_t__ driver_for_each_device (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 TYPE_2__ hfc_driver ; 
 scalar_t__ hfc_jiffies ; 
 TYPE_1__ hfc_tl ; 
 scalar_t__ jiffies ; 
 scalar_t__ tics ; 

__attribute__((used)) static void
hfcpci_softirq(struct timer_list *unused)
{
	WARN_ON_ONCE(driver_for_each_device(&hfc_driver.driver, NULL, NULL,
				      _hfcpci_softirq) != 0);

	/* if next event would be in the past ... */
	if ((s32)(hfc_jiffies + tics - jiffies) <= 0)
		hfc_jiffies = jiffies + 1;
	else
		hfc_jiffies += tics;
	hfc_tl.expires = hfc_jiffies;
	add_timer(&hfc_tl);
}