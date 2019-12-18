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
typedef  scalar_t__ u16 ;
struct adapter {int dummy; } ;

/* Variables and functions */
 scalar_t__ efuse_OneByteRead (struct adapter*,scalar_t__,int*) ; 

__attribute__((used)) static bool hal_EfuseCheckIfDatafollowed(struct adapter *pAdapter, u8 word_cnts, u16 startAddr)
{
	bool ret = false;
	u8 i, efuse_data;

	for (i = 0; i < (word_cnts * 2); i++) {
		if (efuse_OneByteRead(pAdapter, (startAddr + i), &efuse_data) && (efuse_data != 0xFF))
			ret = true;
	}
	return ret;
}