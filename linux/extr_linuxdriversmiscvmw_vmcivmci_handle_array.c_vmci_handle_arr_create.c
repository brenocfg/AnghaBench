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
struct vmci_handle_arr {size_t capacity; scalar_t__ size; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_ATOMIC ; 
 size_t VMCI_HANDLE_ARRAY_DEFAULT_SIZE ; 
 int /*<<< orphan*/  handle_arr_calc_size (size_t) ; 
 struct vmci_handle_arr* kmalloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

struct vmci_handle_arr *vmci_handle_arr_create(size_t capacity)
{
	struct vmci_handle_arr *array;

	if (capacity == 0)
		capacity = VMCI_HANDLE_ARRAY_DEFAULT_SIZE;

	array = kmalloc(handle_arr_calc_size(capacity), GFP_ATOMIC);
	if (!array)
		return NULL;

	array->capacity = capacity;
	array->size = 0;

	return array;
}