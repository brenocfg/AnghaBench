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
struct timer_list {int dummy; } ;
struct adapter {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  set_scan_deny_timer; } ;

/* Variables and functions */
 struct adapter* adapter ; 
 struct adapter* from_timer (int /*<<< orphan*/ ,struct timer_list*,int /*<<< orphan*/ ) ; 
 TYPE_1__ mlmepriv ; 
 int /*<<< orphan*/  rtw_clear_scan_deny (struct adapter*) ; 

__attribute__((used)) static void _rtw_set_scan_deny_timer_hdl(struct timer_list *t)
{
	struct adapter *adapter =
		from_timer(adapter, t, mlmepriv.set_scan_deny_timer);

	rtw_clear_scan_deny(adapter);
}