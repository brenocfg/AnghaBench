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
typedef  int u8 ;
struct lgdt330x_state {int dummy; } ;
typedef  int /*<<< orphan*/  reset ;

/* Variables and functions */
 int IRQ_MASK ; 
 int i2c_write_demod_bytes (struct lgdt330x_state*,int*,int) ; 

__attribute__((used)) static int lgdt3302_sw_reset(struct lgdt330x_state *state)
{
	u8 ret;
	u8 reset[] = {
		IRQ_MASK,
		/*
		 * bit 6 is active low software reset
		 * bits 5-0 are 1 to mask interrupts
		 */
		0x00
	};

	ret = i2c_write_demod_bytes(state,
				    reset, sizeof(reset));
	if (ret == 0) {
		/* force reset high (inactive) and unmask interrupts */
		reset[1] = 0x7f;
		ret = i2c_write_demod_bytes(state,
					    reset, sizeof(reset));
	}
	return ret;
}