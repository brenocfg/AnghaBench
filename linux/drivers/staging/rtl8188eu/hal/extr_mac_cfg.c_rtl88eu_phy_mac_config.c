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
 int ARRAY_SIZE (int*) ; 
 int /*<<< orphan*/  MAX_AGGR_NUM ; 
 int REG_MAX_AGGR_NUM ; 
 int* array_MAC_REG_8188E ; 
 int /*<<< orphan*/  usb_write8 (struct adapter*,int,int /*<<< orphan*/ ) ; 

bool rtl88eu_phy_mac_config(struct adapter *adapt)
{
	u32 i;
	u32 arraylength;
	u32 *ptrarray;

	arraylength = ARRAY_SIZE(array_MAC_REG_8188E);
	ptrarray = array_MAC_REG_8188E;

	for (i = 0; i < arraylength; i += 2)
		usb_write8(adapt, ptrarray[i], (u8)ptrarray[i + 1]);

	usb_write8(adapt, REG_MAX_AGGR_NUM, MAX_AGGR_NUM);
	return true;
}