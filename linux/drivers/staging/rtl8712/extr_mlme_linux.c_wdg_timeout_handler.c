#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct timer_list {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  wdg_timer; } ;
struct _adapter {TYPE_1__ mlmepriv; } ;
struct TYPE_4__ {int /*<<< orphan*/  wdg_timer; } ;

/* Variables and functions */
 struct _adapter* adapter ; 
 struct _adapter* from_timer (int /*<<< orphan*/ ,struct timer_list*,int /*<<< orphan*/ ) ; 
 scalar_t__ jiffies ; 
 TYPE_2__ mlmepriv ; 
 int /*<<< orphan*/  mod_timer (int /*<<< orphan*/ *,scalar_t__) ; 
 scalar_t__ msecs_to_jiffies (int) ; 
 int /*<<< orphan*/  r8712_wdg_wk_cmd (struct _adapter*) ; 

__attribute__((used)) static void wdg_timeout_handler (struct timer_list *t)
{
	struct _adapter *adapter =
		from_timer(adapter, t, mlmepriv.wdg_timer);

	r8712_wdg_wk_cmd(adapter);

	mod_timer(&adapter->mlmepriv.wdg_timer,
		  jiffies + msecs_to_jiffies(2000));
}