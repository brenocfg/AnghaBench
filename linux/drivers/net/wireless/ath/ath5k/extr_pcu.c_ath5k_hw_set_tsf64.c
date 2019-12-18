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
typedef  int u64 ;
struct ath5k_hw {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  AR5K_TSF_L32 ; 
 int /*<<< orphan*/  AR5K_TSF_U32 ; 
 int /*<<< orphan*/  ath5k_hw_reg_write (struct ath5k_hw*,int,int /*<<< orphan*/ ) ; 

void
ath5k_hw_set_tsf64(struct ath5k_hw *ah, u64 tsf64)
{
	ath5k_hw_reg_write(ah, tsf64 & 0xffffffff, AR5K_TSF_L32);
	ath5k_hw_reg_write(ah, (tsf64 >> 32) & 0xffffffff, AR5K_TSF_U32);
}