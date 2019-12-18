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
typedef  int u32 ;
struct tca8418_keypad {int dummy; } ;

/* Variables and functions */
 int CFG_INT_CFG ; 
 int CFG_KE_IEN ; 
 int CFG_OVR_FLOW_IEN ; 
 int /*<<< orphan*/  REG_CFG ; 
 int /*<<< orphan*/  REG_DEBOUNCE_DIS1 ; 
 int /*<<< orphan*/  REG_DEBOUNCE_DIS2 ; 
 int /*<<< orphan*/  REG_DEBOUNCE_DIS3 ; 
 int /*<<< orphan*/  REG_KP_GPIO1 ; 
 int /*<<< orphan*/  REG_KP_GPIO2 ; 
 int /*<<< orphan*/  REG_KP_GPIO3 ; 
 int tca8418_write_byte (struct tca8418_keypad*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int tca8418_configure(struct tca8418_keypad *keypad_data,
			     u32 rows, u32 cols)
{
	int reg, error = 0;

	/* Assemble a mask for row and column registers */
	reg  =  ~(~0 << rows);
	reg += (~(~0 << cols)) << 8;

	/* Set registers to keypad mode */
	error |= tca8418_write_byte(keypad_data, REG_KP_GPIO1, reg);
	error |= tca8418_write_byte(keypad_data, REG_KP_GPIO2, reg >> 8);
	error |= tca8418_write_byte(keypad_data, REG_KP_GPIO3, reg >> 16);

	/* Enable column debouncing */
	error |= tca8418_write_byte(keypad_data, REG_DEBOUNCE_DIS1, reg);
	error |= tca8418_write_byte(keypad_data, REG_DEBOUNCE_DIS2, reg >> 8);
	error |= tca8418_write_byte(keypad_data, REG_DEBOUNCE_DIS3, reg >> 16);

	if (error)
		return error;

	error = tca8418_write_byte(keypad_data, REG_CFG,
				CFG_INT_CFG | CFG_OVR_FLOW_IEN | CFG_KE_IEN);

	return error;
}