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

/* Variables and functions */
 int /*<<< orphan*/  CURRENT_GATE ; 
 unsigned int CURRENT_GATE_M2XCLK_DIV_1 ; 
 unsigned int CURRENT_GATE_M2XCLK_DIV_2 ; 
 unsigned int CURRENT_GATE_M2XCLK_DIV_3 ; 
 unsigned int CURRENT_GATE_M2XCLK_DIV_4 ; 
 unsigned int CURRENT_GATE_M2XCLK_MASK ; 
 unsigned int DIV_ROUND_CLOSEST (int /*<<< orphan*/ ,unsigned int) ; 
 unsigned int MHz (int) ; 
 scalar_t__ SM750LE ; 
 int /*<<< orphan*/  get_mxclk_freq () ; 
 unsigned int peek32 (int /*<<< orphan*/ ) ; 
 scalar_t__ sm750_get_chip_type () ; 
 int /*<<< orphan*/  sm750_set_current_gate (unsigned int) ; 

__attribute__((used)) static void set_memory_clock(unsigned int frequency)
{
	unsigned int reg, divisor;

	/*
	 * Cheok_0509: For SM750LE, the memory clock is fixed.
	 * Nothing to set.
	 */
	if (sm750_get_chip_type() == SM750LE)
		return;

	if (frequency) {
		/*
		 * Set the frequency to the maximum frequency
		 * that the DDR Memory can take which is 336MHz.
		 */
		if (frequency > MHz(336))
			frequency = MHz(336);

		/* Calculate the divisor */
		divisor = DIV_ROUND_CLOSEST(get_mxclk_freq(), frequency);

		/* Set the corresponding divisor in the register. */
		reg = peek32(CURRENT_GATE) & ~CURRENT_GATE_M2XCLK_MASK;
		switch (divisor) {
		default:
		case 1:
			reg |= CURRENT_GATE_M2XCLK_DIV_1;
			break;
		case 2:
			reg |= CURRENT_GATE_M2XCLK_DIV_2;
			break;
		case 3:
			reg |= CURRENT_GATE_M2XCLK_DIV_3;
			break;
		case 4:
			reg |= CURRENT_GATE_M2XCLK_DIV_4;
			break;
		}

		sm750_set_current_gate(reg);
	}
}