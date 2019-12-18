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
typedef  scalar_t__ u8 ;
typedef  int u16 ;

/* Variables and functions */

bool ath9k_hw_get_lower_upper_index(u8 target, u8 *pList, u16 listSize,
				    u16 *indexL, u16 *indexR)
{
	u16 i;

	if (target <= pList[0]) {
		*indexL = *indexR = 0;
		return true;
	}
	if (target >= pList[listSize - 1]) {
		*indexL = *indexR = (u16) (listSize - 1);
		return true;
	}

	for (i = 0; i < listSize - 1; i++) {
		if (pList[i] == target) {
			*indexL = *indexR = i;
			return true;
		}
		if (target < pList[i + 1]) {
			*indexL = i;
			*indexR = (u16) (i + 1);
			return false;
		}
	}
	return false;
}