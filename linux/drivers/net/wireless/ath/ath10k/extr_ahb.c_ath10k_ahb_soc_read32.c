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
 scalar_t__ RTC_SOC_BASE_ADDRESS ; 
 scalar_t__ ath10k_ahb_read32 (struct ath10k*,scalar_t__) ; 

__attribute__((used)) static u32 ath10k_ahb_soc_read32(struct ath10k *ar, u32 addr)
{
	return ath10k_ahb_read32(ar, RTC_SOC_BASE_ADDRESS + addr);
}