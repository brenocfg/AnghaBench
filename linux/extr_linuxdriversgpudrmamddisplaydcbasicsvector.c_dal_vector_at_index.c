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
struct vector {void* container; int count; int struct_size; } ;

/* Variables and functions */

void *dal_vector_at_index(
	const struct vector *vector,
	uint32_t index)
{
	if (vector->container == NULL || index >= vector->count)
		return NULL;
	return vector->container + (index * vector->struct_size);
}