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

/* Variables and functions */
 int /*<<< orphan*/  ath5k_debug_printrxbuffs (struct ath5k_hw*) ; 
 int /*<<< orphan*/  ath5k_hw_set_rx_filter (struct ath5k_hw*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ath5k_hw_stop_rx_pcu (struct ath5k_hw*) ; 

__attribute__((used)) static void
ath5k_rx_stop(struct ath5k_hw *ah)
{

	ath5k_hw_set_rx_filter(ah, 0);	/* clear recv filter */
	ath5k_hw_stop_rx_pcu(ah);	/* disable PCU */

	ath5k_debug_printrxbuffs(ah);
}