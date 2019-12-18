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
typedef  int uint32_t ;
struct csio_hw {int dummy; } ;

/* Variables and functions */
 int EAGAIN ; 
 int csio_rd_reg32 (struct csio_hw*,int) ; 
 int /*<<< orphan*/  udelay (int) ; 

int
csio_hw_wait_op_done_val(struct csio_hw *hw, int reg, uint32_t mask,
			 int polarity, int attempts, int delay, uint32_t *valp)
{
	uint32_t val;
	while (1) {
		val = csio_rd_reg32(hw, reg);

		if (!!(val & mask) == polarity) {
			if (valp)
				*valp = val;
			return 0;
		}

		if (--attempts == 0)
			return -EAGAIN;
		if (delay)
			udelay(delay);
	}
}