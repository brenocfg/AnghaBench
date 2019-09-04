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
typedef  scalar_t__ uint ;
struct ksz_hw {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  hw_ena_intr (struct ksz_hw*) ; 

__attribute__((used)) static inline void hw_restore_intr(struct ksz_hw *hw, uint interrupt)
{
	if (interrupt)
		hw_ena_intr(hw);
}