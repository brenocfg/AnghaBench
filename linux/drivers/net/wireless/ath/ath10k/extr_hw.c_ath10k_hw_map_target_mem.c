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
 scalar_t__ FW_RAM_CONFIG_ADDRESS ; 
 scalar_t__ SOC_CORE_BASE_ADDRESS ; 
 int /*<<< orphan*/  ath10k_hif_write32 (struct ath10k*,scalar_t__,scalar_t__) ; 

__attribute__((used)) static void ath10k_hw_map_target_mem(struct ath10k *ar, u32 msb)
{
	u32 address = SOC_CORE_BASE_ADDRESS + FW_RAM_CONFIG_ADDRESS;

	ath10k_hif_write32(ar, address, msb);
}