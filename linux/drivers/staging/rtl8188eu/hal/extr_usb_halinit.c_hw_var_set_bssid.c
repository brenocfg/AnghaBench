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
typedef  int u8 ;
typedef  scalar_t__ u32 ;
struct adapter {int dummy; } ;

/* Variables and functions */
 scalar_t__ REG_BSSID ; 
 int /*<<< orphan*/  usb_write8 (struct adapter*,scalar_t__,int) ; 

__attribute__((used)) static void hw_var_set_bssid(struct adapter *Adapter, u8 variable, u8 *val)
{
	u8 idx = 0;
	u32 reg_bssid;

	reg_bssid = REG_BSSID;

	for (idx = 0; idx < 6; idx++)
		usb_write8(Adapter, (reg_bssid + idx), val[idx]);
}