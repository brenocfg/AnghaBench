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
struct ath5k_hw {int dummy; } ;
typedef  int /*<<< orphan*/  s32 ;

/* Variables and functions */
 int /*<<< orphan*/  AR5K_PHY_NF ; 
 int /*<<< orphan*/  AR5K_PHY_NF_MINCCA_PWR ; 
 int /*<<< orphan*/  AR5K_REG_MS (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ath5k_hw_reg_read (struct ath5k_hw*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sign_extend32 (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static s32
ath5k_hw_read_measured_noise_floor(struct ath5k_hw *ah)
{
	s32 val;

	val = ath5k_hw_reg_read(ah, AR5K_PHY_NF);
	return sign_extend32(AR5K_REG_MS(val, AR5K_PHY_NF_MINCCA_PWR), 8);
}