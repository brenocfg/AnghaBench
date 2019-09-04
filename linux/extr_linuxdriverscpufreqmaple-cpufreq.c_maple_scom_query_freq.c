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

/* Variables and functions */
 unsigned long PCR_SPEED_SHIFT ; 
 unsigned long PSR_CUR_SPEED_SHIFT ; 
 int /*<<< orphan*/  SCOM_PSR ; 
 unsigned long* maple_pmode_data ; 
 int maple_pmode_max ; 
 unsigned long scom970_read (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int maple_scom_query_freq(void)
{
	unsigned long psr = scom970_read(SCOM_PSR);
	int i;

	for (i = 0; i <= maple_pmode_max; i++)
		if ((((psr >> PSR_CUR_SPEED_SHIFT) ^
		      (maple_pmode_data[i] >> PCR_SPEED_SHIFT)) & 0x3) == 0)
			break;
	return i;
}