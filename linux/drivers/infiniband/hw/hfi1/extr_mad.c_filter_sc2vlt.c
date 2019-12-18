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
 int ILLEGAL_VL ; 
 int OPA_MAX_SCS ; 

__attribute__((used)) static void filter_sc2vlt(void *data, bool set)
{
	int i;
	u8 *pd = data;

	for (i = 0; i < OPA_MAX_SCS; i++) {
		if (i == 15)
			continue;

		if (set) {
			if ((pd[i] & 0x1f) == 0xf)
				pd[i] = ILLEGAL_VL;
		} else {
			if ((pd[i] & 0x1f) == ILLEGAL_VL)
				pd[i] = 0xf;
		}
	}
}