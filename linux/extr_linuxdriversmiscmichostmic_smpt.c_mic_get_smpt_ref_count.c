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
typedef  scalar_t__ u64 ;
struct mic_device {int dummy; } ;
typedef  scalar_t__ s64 ;
typedef  scalar_t__ dma_addr_t ;

/* Variables and functions */
 scalar_t__ mic_smpt_align_high (struct mic_device*,scalar_t__) ; 
 scalar_t__ mic_smpt_align_low (struct mic_device*,scalar_t__) ; 
 scalar_t__ min (scalar_t__,scalar_t__) ; 

__attribute__((used)) static int mic_get_smpt_ref_count(struct mic_device *mdev, dma_addr_t dma_addr,
				  size_t size, s64 *ref,  u64 *smpt_start)
{
	u64 start =  dma_addr;
	u64 end = dma_addr + size;
	int i = 0;

	while (start < end) {
		ref[i++] = min(mic_smpt_align_high(mdev, start + 1),
			end) - start;
		start = mic_smpt_align_high(mdev, start + 1);
	}

	if (smpt_start)
		*smpt_start = mic_smpt_align_low(mdev, dma_addr);

	return i;
}