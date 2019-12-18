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
struct ath_hw {int dummy; } ;

/* Variables and functions */
 int ar9003_hw_get_rx_gain_idx (struct ath_hw*) ; 
 int /*<<< orphan*/  ar9003_rx_gain_table_mode0 (struct ath_hw*) ; 
 int /*<<< orphan*/  ar9003_rx_gain_table_mode1 (struct ath_hw*) ; 
 int /*<<< orphan*/  ar9003_rx_gain_table_mode2 (struct ath_hw*) ; 
 int /*<<< orphan*/  ar9003_rx_gain_table_mode3 (struct ath_hw*) ; 

__attribute__((used)) static void ar9003_rx_gain_table_apply(struct ath_hw *ah)
{
	switch (ar9003_hw_get_rx_gain_idx(ah)) {
	case 0:
	default:
		ar9003_rx_gain_table_mode0(ah);
		break;
	case 1:
		ar9003_rx_gain_table_mode1(ah);
		break;
	case 2:
		ar9003_rx_gain_table_mode2(ah);
		break;
	case 3:
		ar9003_rx_gain_table_mode3(ah);
		break;
	}
}