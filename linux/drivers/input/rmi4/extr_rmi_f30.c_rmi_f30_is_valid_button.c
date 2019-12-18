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
struct rmi_f30_ctrl_data {int* regs; } ;

/* Variables and functions */
 int BIT (int) ; 

__attribute__((used)) static bool rmi_f30_is_valid_button(int button, struct rmi_f30_ctrl_data *ctrl)
{
	int byte_position = button >> 3;
	int bit_position = button & 0x07;

	/*
	 * ctrl2 -> dir == 0 -> input mode
	 * ctrl3 -> data == 1 -> actual button
	 */
	return !(ctrl[2].regs[byte_position] & BIT(bit_position)) &&
		(ctrl[3].regs[byte_position] & BIT(bit_position));
}