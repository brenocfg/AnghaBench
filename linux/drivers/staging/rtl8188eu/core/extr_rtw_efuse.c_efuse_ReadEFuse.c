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
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u16 ;
struct adapter {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  iol_mode_enable (struct adapter*,int) ; 
 int /*<<< orphan*/  iol_read_efuse (struct adapter*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rtw_hal_power_on (struct adapter*) ; 
 scalar_t__ rtw_iol_applied (struct adapter*) ; 

void efuse_ReadEFuse(struct adapter *Adapter, u8 efuseType, u16 _offset, u16 _size_byte, u8 *pbuf)
{
	if (rtw_iol_applied(Adapter)) {
		rtw_hal_power_on(Adapter);
		iol_mode_enable(Adapter, 1);
		iol_read_efuse(Adapter, 0, _offset, _size_byte, pbuf);
		iol_mode_enable(Adapter, 0);
	}
}