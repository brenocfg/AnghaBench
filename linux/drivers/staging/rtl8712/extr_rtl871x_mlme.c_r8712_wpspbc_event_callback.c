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
typedef  int /*<<< orphan*/  u8 ;
struct TYPE_2__ {int wps_hw_pbc_pressed; } ;
struct _adapter {TYPE_1__ securitypriv; } ;

/* Variables and functions */

void r8712_wpspbc_event_callback(struct _adapter *adapter, u8 *pbuf)
{
	if (!adapter->securitypriv.wps_hw_pbc_pressed)
		adapter->securitypriv.wps_hw_pbc_pressed = true;
}