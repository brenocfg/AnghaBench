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
struct TYPE_3__ {int busetkipkey; } ;
struct _adapter {TYPE_1__ securitypriv; } ;
struct TYPE_4__ {int /*<<< orphan*/  tkip_timer; } ;

/* Variables and functions */
 struct _adapter* from_timer (int /*<<< orphan*/ ,struct timer_list*,int /*<<< orphan*/ ) ; 
 struct _adapter* padapter ; 
 TYPE_2__ securitypriv ; 

void r8712_use_tkipkey_handler(struct timer_list *t)
{
	struct _adapter *padapter =
		from_timer(padapter, t, securitypriv.tkip_timer);

	padapter->securitypriv.busetkipkey = true;
}