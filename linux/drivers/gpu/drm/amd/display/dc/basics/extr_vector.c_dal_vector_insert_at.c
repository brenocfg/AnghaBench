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
typedef  void const uint8_t ;
typedef  int uint32_t ;
struct vector {int count; int capacity; void* container; int struct_size; } ;

/* Variables and functions */
 int /*<<< orphan*/  calc_increased_capacity (int) ; 
 int /*<<< orphan*/  dal_vector_reserve (struct vector*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memmove (void const*,void const*,int) ; 

bool dal_vector_insert_at(
	struct vector *vector,
	const void *what,
	uint32_t position)
{
	uint8_t *insert_address;

	if (vector->count == vector->capacity) {
		if (!dal_vector_reserve(
			vector,
			calc_increased_capacity(vector->capacity)))
			return false;
	}

	insert_address = vector->container + (vector->struct_size * position);

	if (vector->count && position < vector->count)
		memmove(
			insert_address + vector->struct_size,
			insert_address,
			vector->struct_size * (vector->count - position));

	memmove(
		insert_address,
		what,
		vector->struct_size);

	vector->count++;

	return true;
}