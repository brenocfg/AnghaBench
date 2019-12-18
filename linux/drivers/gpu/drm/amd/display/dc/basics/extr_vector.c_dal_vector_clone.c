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
typedef  scalar_t__ uint32_t ;
struct vector {int capacity; int struct_size; int /*<<< orphan*/  container; int /*<<< orphan*/  ctx; } ;

/* Variables and functions */
 int /*<<< orphan*/  BREAK_TO_DEBUGGER () ; 
 struct vector* dal_vector_create (int /*<<< orphan*/ ,int,int) ; 
 scalar_t__ dal_vector_get_count (struct vector const*) ; 
 struct vector* dal_vector_presized_create (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  memmove (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

struct vector *dal_vector_clone(
	const struct vector *vector)
{
	struct vector *vec_cloned;
	uint32_t count;

	/* create new vector */
	count = dal_vector_get_count(vector);

	if (count == 0)
		/* when count is 0 we still want to create clone of the vector
		 */
		vec_cloned = dal_vector_create(
			vector->ctx,
			vector->capacity,
			vector->struct_size);
	else
		/* Call "presized create" version, independently of how the
		 * original vector was created.
		 * The owner of original vector must know how to treat the new
		 * vector - as "presized" or as "regular".
		 * But from vector point of view it doesn't matter. */
		vec_cloned = dal_vector_presized_create(vector->ctx, count,
			NULL,/* no initial value */
			vector->struct_size);

	if (NULL == vec_cloned) {
		BREAK_TO_DEBUGGER();
		return NULL;
	}

	/* copy vector's data */
	memmove(vec_cloned->container, vector->container,
			vec_cloned->struct_size * vec_cloned->capacity);

	return vec_cloned;
}