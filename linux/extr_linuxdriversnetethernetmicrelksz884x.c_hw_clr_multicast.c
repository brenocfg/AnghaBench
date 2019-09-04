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
struct ksz_hw {scalar_t__ io; scalar_t__* multi_bits; } ;

/* Variables and functions */
 int HW_MULTICAST_SIZE ; 
 scalar_t__ KS884X_MULTICAST_0_OFFSET ; 
 int /*<<< orphan*/  writeb (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void hw_clr_multicast(struct ksz_hw *hw)
{
	int i;

	for (i = 0; i < HW_MULTICAST_SIZE; i++) {
		hw->multi_bits[i] = 0;

		writeb(0, hw->io + KS884X_MULTICAST_0_OFFSET + i);
	}
}