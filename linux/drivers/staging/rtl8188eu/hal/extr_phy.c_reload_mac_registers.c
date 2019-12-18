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
typedef  int u32 ;
struct adapter {int dummy; } ;

/* Variables and functions */
 int IQK_MAC_REG_NUM ; 
 int /*<<< orphan*/  usb_write32 (struct adapter*,int,int) ; 
 int /*<<< orphan*/  usb_write8 (struct adapter*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void reload_mac_registers(struct adapter *adapt,
				 u32 *mac_reg, u32 *backup)
{
	u32 i;

	for (i = 0; i < (IQK_MAC_REG_NUM - 1); i++)
		usb_write8(adapt, mac_reg[i], (u8)backup[i]);

	usb_write32(adapt, mac_reg[i], backup[i]);
}