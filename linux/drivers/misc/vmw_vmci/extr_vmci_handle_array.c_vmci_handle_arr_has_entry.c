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
typedef  size_t u32 ;
struct vmci_handle_arr {size_t size; int /*<<< orphan*/ * entries; } ;
struct vmci_handle {int dummy; } ;

/* Variables and functions */
 scalar_t__ vmci_handle_is_equal (int /*<<< orphan*/ ,struct vmci_handle) ; 

bool vmci_handle_arr_has_entry(const struct vmci_handle_arr *array,
			       struct vmci_handle entry_handle)
{
	u32 i;

	for (i = 0; i < array->size; i++)
		if (vmci_handle_is_equal(array->entries[i], entry_handle))
			return true;

	return false;
}