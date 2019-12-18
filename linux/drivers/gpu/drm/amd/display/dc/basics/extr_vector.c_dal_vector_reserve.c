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
struct vector {int capacity; int struct_size; void* container; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 void* krealloc (void*,int,int /*<<< orphan*/ ) ; 

bool dal_vector_reserve(struct vector *vector, uint32_t capacity)
{
	void *new_container;

	if (capacity <= vector->capacity)
		return true;

	new_container = krealloc(vector->container,
				 capacity * vector->struct_size, GFP_KERNEL);

	if (new_container) {
		vector->container = new_container;
		vector->capacity = capacity;
		return true;
	}

	return false;
}