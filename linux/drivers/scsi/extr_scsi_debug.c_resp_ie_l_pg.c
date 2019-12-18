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
typedef  int /*<<< orphan*/  ie_l_pg ;

/* Variables and functions */
 unsigned char THRESHOLD_EXCEEDED ; 
 int* iec_m_pg ; 
 int /*<<< orphan*/  memcpy (unsigned char*,unsigned char*,int) ; 

__attribute__((used)) static int resp_ie_l_pg(unsigned char *arr)
{
	unsigned char ie_l_pg[] = {0x0, 0x0, 0x3, 0x3, 0x0, 0x0, 38,
		};

	memcpy(arr, ie_l_pg, sizeof(ie_l_pg));
	if (iec_m_pg[2] & 0x4) {	/* TEST bit set */
		arr[4] = THRESHOLD_EXCEEDED;
		arr[5] = 0xff;
	}
	return sizeof(ie_l_pg);
}