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
typedef  enum dpms { ____Placeholder_dpms } dpms ;

/* Variables and functions */
 int /*<<< orphan*/  CRT_DISPLAY_CTRL ; 
 unsigned int CRT_DISPLAY_CTRL_DPMS_MASK ; 
 int CRT_DISPLAY_CTRL_DPMS_SHIFT ; 
 scalar_t__ SM750LE ; 
 int /*<<< orphan*/  SYSTEM_CTRL ; 
 unsigned int SYSTEM_CTRL_DPMS_MASK ; 
 unsigned int peek32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  poke32 (int /*<<< orphan*/ ,unsigned int) ; 
 scalar_t__ sm750_get_chip_type () ; 

void ddk750_set_dpms(enum dpms state)
{
	unsigned int value;

	if (sm750_get_chip_type() == SM750LE) {
		value = peek32(CRT_DISPLAY_CTRL) & ~CRT_DISPLAY_CTRL_DPMS_MASK;
		value |= (state << CRT_DISPLAY_CTRL_DPMS_SHIFT);
		poke32(CRT_DISPLAY_CTRL, value);
	} else {
		value = peek32(SYSTEM_CTRL);
		value = (value & ~SYSTEM_CTRL_DPMS_MASK) | state;
		poke32(SYSTEM_CTRL, value);
	}
}