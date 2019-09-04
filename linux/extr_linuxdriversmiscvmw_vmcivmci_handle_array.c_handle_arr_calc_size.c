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
struct vmci_handle_arr {int dummy; } ;
struct vmci_handle {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static size_t handle_arr_calc_size(size_t capacity)
{
	return sizeof(struct vmci_handle_arr) +
	    capacity * sizeof(struct vmci_handle);
}