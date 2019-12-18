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
struct TYPE_3__ {int fw_iol; } ;
struct adapter {TYPE_1__ registrypriv; } ;
struct TYPE_4__ {int /*<<< orphan*/  ishighspeed; } ;

/* Variables and functions */
 TYPE_2__* adapter_to_dvobj (struct adapter*) ; 

bool rtw_iol_applied(struct adapter *adapter)
{
	if (adapter->registrypriv.fw_iol == 1)
		return true;

	if (adapter->registrypriv.fw_iol == 2 &&
	    !adapter_to_dvobj(adapter)->ishighspeed)
		return true;
	return false;
}