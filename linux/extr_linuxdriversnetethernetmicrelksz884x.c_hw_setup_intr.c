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
struct ksz_hw {int intr_mask; } ;

/* Variables and functions */
 int KS884X_INT_MASK ; 
 int KS884X_INT_RX_OVERRUN ; 

__attribute__((used)) static void hw_setup_intr(struct ksz_hw *hw)
{
	hw->intr_mask = KS884X_INT_MASK | KS884X_INT_RX_OVERRUN;
}