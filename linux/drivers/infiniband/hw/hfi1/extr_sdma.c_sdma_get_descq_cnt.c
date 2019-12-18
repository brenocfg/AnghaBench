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
typedef  int u16 ;

/* Variables and functions */
 int SDMA_DESCQ_CNT ; 
 int /*<<< orphan*/  is_power_of_2 (int) ; 
 int sdma_descq_cnt ; 

u16 sdma_get_descq_cnt(void)
{
	u16 count = sdma_descq_cnt;

	if (!count)
		return SDMA_DESCQ_CNT;
	/* count must be a power of 2 greater than 64 and less than
	 * 32768.   Otherwise return default.
	 */
	if (!is_power_of_2(count))
		return SDMA_DESCQ_CNT;
	if (count < 64 || count > 32768)
		return SDMA_DESCQ_CNT;
	return count;
}