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
typedef  scalar_t__ u32 ;
struct ath10k {int dummy; } ;

/* Variables and functions */
 scalar_t__ DRAM_BASE_ADDRESS ; 
 scalar_t__ REGION_ACCESS_SIZE_LIMIT ; 
 int ath10k_hif_diag_write (struct ath10k*,scalar_t__,void const*,scalar_t__) ; 
 int ath10k_hw_diag_segment_msb_download (struct ath10k*,void const*,scalar_t__,scalar_t__) ; 

__attribute__((used)) static int ath10k_hw_diag_segment_download(struct ath10k *ar,
					   const void *buffer,
					   u32 address,
					   u32 length)
{
	if (address >= DRAM_BASE_ADDRESS + REGION_ACCESS_SIZE_LIMIT)
		/* Needs to change MSB for memory write */
		return ath10k_hw_diag_segment_msb_download(ar, buffer,
							   address, length);
	else
		return ath10k_hif_diag_write(ar, address, buffer, length);
}