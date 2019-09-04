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
 unsigned int MPIC_MSGR_REGISTERS_PER_BLOCK ; 
 unsigned int mpic_msgr_number_of_blocks () ; 

__attribute__((used)) static unsigned int mpic_msgr_number_of_registers(void)
{
	return mpic_msgr_number_of_blocks() * MPIC_MSGR_REGISTERS_PER_BLOCK;
}