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
typedef  int u32 ;

/* Variables and functions */
 int ET_DMA10_MASK ; 
 int ET_DMA10_WRAP ; 

__attribute__((used)) static inline u32 bump_free_buff_ring(u32 *free_buff_ring, u32 limit)
{
	u32 tmp_free_buff_ring = *free_buff_ring;

	tmp_free_buff_ring++;
	/* This works for all cases where limit < 1024. The 1023 case
	 * works because 1023++ is 1024 which means the if condition is not
	 * taken but the carry of the bit into the wrap bit toggles the wrap
	 * value correctly
	 */
	if ((tmp_free_buff_ring & ET_DMA10_MASK) > limit) {
		tmp_free_buff_ring &= ~ET_DMA10_MASK;
		tmp_free_buff_ring ^= ET_DMA10_WRAP;
	}
	/* For the 1023 case */
	tmp_free_buff_ring &= (ET_DMA10_MASK | ET_DMA10_WRAP);
	*free_buff_ring = tmp_free_buff_ring;
	return tmp_free_buff_ring;
}