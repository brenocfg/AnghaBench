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
struct vmci_handle_arr {size_t size; } ;

/* Variables and functions */

__attribute__((used)) static inline size_t vmci_handle_arr_get_size(
	const struct vmci_handle_arr *array)
{
	return array->size;
}