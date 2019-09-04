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
typedef  int /*<<< orphan*/  u32 ;
struct atl1e_hw {int dummy; } ;

/* Variables and functions */

bool atl1e_write_eeprom(struct atl1e_hw *hw, u32 offset, u32 value)
{
	return true;
}