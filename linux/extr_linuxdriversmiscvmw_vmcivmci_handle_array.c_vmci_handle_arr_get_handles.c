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
struct vmci_handle_arr {struct vmci_handle* entries; scalar_t__ size; } ;
struct vmci_handle {int dummy; } ;

/* Variables and functions */

struct vmci_handle *vmci_handle_arr_get_handles(struct vmci_handle_arr *array)
{
	if (array->size)
		return array->entries;

	return NULL;
}