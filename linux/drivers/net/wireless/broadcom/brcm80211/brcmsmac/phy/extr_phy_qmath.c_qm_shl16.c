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
typedef  int s16 ;

/* Variables and functions */
 int qm_add16 (int,int) ; 

s16 qm_shl16(s16 op, int shift)
{
	int i;
	s16 result;
	result = op;
	if (shift > 15)
		shift = 15;
	else if (shift < -15)
		shift = -15;
	if (shift > 0) {
		for (i = 0; i < shift; i++)
			result = qm_add16(result, result);
	} else {
		result = result >> (-shift);
	}

	return result;
}