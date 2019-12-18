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
struct ath5k_hw {int /*<<< orphan*/  ah_mac_srev; } ;

/* Variables and functions */
 int /*<<< orphan*/  AR5K_SREV ; 
 int /*<<< orphan*/  ath5k_hw_reg_read (struct ath5k_hw*,int /*<<< orphan*/ ) ; 

int ath5k_hw_read_srev(struct ath5k_hw *ah)
{
	ah->ah_mac_srev = ath5k_hw_reg_read(ah, AR5K_SREV);
	return 0;
}