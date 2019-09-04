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
typedef  int uint32_t ;
struct vector {int count; int struct_size; scalar_t__ container; } ;

/* Variables and functions */
 int /*<<< orphan*/  memmove (scalar_t__,scalar_t__,int) ; 

bool dal_vector_remove_at_index(
	struct vector *vector,
	uint32_t index)
{
	if (index >= vector->count)
		return false;

	if (index != vector->count - 1)
		memmove(
			vector->container + (index * vector->struct_size),
			vector->container + ((index + 1) * vector->struct_size),
			(vector->count - index - 1) * vector->struct_size);
	vector->count -= 1;

	return true;
}