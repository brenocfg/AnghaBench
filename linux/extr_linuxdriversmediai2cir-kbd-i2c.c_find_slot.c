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
typedef  scalar_t__ u16 ;

/* Variables and functions */
 scalar_t__ get_unaligned_be16 (scalar_t__*) ; 
 int /*<<< orphan*/  put_unaligned_be16 (scalar_t__,scalar_t__*) ; 

__attribute__((used)) static int find_slot(u16 *array, unsigned int size, u16 val)
{
	int i;

	for (i = 0; i < size; i++) {
		if (get_unaligned_be16(&array[i]) == val) {
			return i;
		} else if (!array[i]) {
			put_unaligned_be16(val, &array[i]);
			return i;
		}
	}

	return -1;
}