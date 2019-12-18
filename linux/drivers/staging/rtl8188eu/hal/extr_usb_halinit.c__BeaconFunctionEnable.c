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
struct adapter {int dummy; } ;

/* Variables and functions */
 int BIT (int) ; 
 scalar_t__ REG_BCN_CTRL ; 
 scalar_t__ REG_RD_CTRL ; 
 int /*<<< orphan*/  usb_write8 (struct adapter*,scalar_t__,int) ; 

__attribute__((used)) static void _BeaconFunctionEnable(struct adapter *Adapter,
				  bool Enable, bool Linked)
{
	usb_write8(Adapter, REG_BCN_CTRL, (BIT(4) | BIT(3) | BIT(1)));

	usb_write8(Adapter, REG_RD_CTRL + 1, 0x6F);
}