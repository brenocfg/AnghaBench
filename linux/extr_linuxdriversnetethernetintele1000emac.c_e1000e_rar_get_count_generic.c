#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_2__ {int /*<<< orphan*/  rar_entry_count; } ;
struct e1000_hw {TYPE_1__ mac; } ;

/* Variables and functions */

u32 e1000e_rar_get_count_generic(struct e1000_hw *hw)
{
	return hw->mac.rar_entry_count;
}