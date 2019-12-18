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
struct TYPE_4__ {scalar_t__ power_mgnt; int /*<<< orphan*/  smart_ps; } ;
struct TYPE_3__ {scalar_t__ pwr_mode; } ;
struct _adapter {TYPE_2__ registrypriv; TYPE_1__ pwrctrlpriv; scalar_t__ surprise_removed; scalar_t__ driver_stopped; } ;

/* Variables and functions */
 int /*<<< orphan*/  r8712_set_ps_mode (struct _adapter*,scalar_t__,int /*<<< orphan*/ ) ; 

void _r8712_dhcp_timeout_handler (struct _adapter *adapter)
{
	if (adapter->driver_stopped || adapter->surprise_removed)
		return;
	if (adapter->pwrctrlpriv.pwr_mode != adapter->registrypriv.power_mgnt)
		r8712_set_ps_mode(adapter, adapter->registrypriv.power_mgnt,
			    adapter->registrypriv.smart_ps);
}