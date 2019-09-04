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

/* Variables and functions */
 int LM93_TEMP_OFFSET_FROM_REG (int,int) ; 

__attribute__((used)) static int LM93_TEMP_AUTO_OFFSET_FROM_REG(u8 reg, int nr, int mode)
{
	/* temp1-temp2 (nr=0,1) use lower nibble */
	if (nr < 2)
		return LM93_TEMP_OFFSET_FROM_REG(reg & 0x0f, mode);

	/* temp3-temp4 (nr=2,3) use upper nibble */
	else
		return LM93_TEMP_OFFSET_FROM_REG(reg >> 4 & 0x0f, mode);
}