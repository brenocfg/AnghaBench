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
struct vector {int capacity; int struct_size; int count; int /*<<< orphan*/ * container; } ;
struct dc_context {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BREAK_TO_DEBUGGER () ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/ * kcalloc (int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memmove (int /*<<< orphan*/ *,void*,int) ; 

bool dal_vector_presized_costruct(
	struct vector *vector,
	struct dc_context *ctx,
	uint32_t count,
	void *initial_value,
	uint32_t struct_size)
{
	uint32_t i;

	vector->container = NULL;

	if (!struct_size || !count) {
		/* Container must be non-zero size*/
		BREAK_TO_DEBUGGER();
		return false;
	}

	vector->container = kcalloc(count, struct_size, GFP_KERNEL);

	if (vector->container == NULL)
		return false;

	/* If caller didn't supply initial value then the default
	 * of all zeros is expected, which is exactly what dal_alloc()
	 * initialises the memory to. */
	if (NULL != initial_value) {
		for (i = 0; i < count; ++i)
			memmove(
				vector->container + i * struct_size,
				initial_value,
				struct_size);
	}

	vector->capacity = count;
	vector->struct_size = struct_size;
	vector->count = count;
	return true;
}