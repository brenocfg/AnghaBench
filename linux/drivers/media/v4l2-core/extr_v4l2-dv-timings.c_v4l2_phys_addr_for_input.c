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
typedef  int u16 ;

/* Variables and functions */
 int CEC_PHYS_ADDR_INVALID ; 
 scalar_t__ WARN_ON (int) ; 

u16 v4l2_phys_addr_for_input(u16 phys_addr, u8 input)
{
	/* Check if input is sane */
	if (WARN_ON(input == 0 || input > 0xf))
		return CEC_PHYS_ADDR_INVALID;

	if (phys_addr == 0)
		return input << 12;

	if ((phys_addr & 0x0fff) == 0)
		return phys_addr | (input << 8);

	if ((phys_addr & 0x00ff) == 0)
		return phys_addr | (input << 4);

	if ((phys_addr & 0x000f) == 0)
		return phys_addr | input;

	/*
	 * All nibbles are used so no valid physical addresses can be assigned
	 * to the input.
	 */
	return CEC_PHYS_ADDR_INVALID;
}