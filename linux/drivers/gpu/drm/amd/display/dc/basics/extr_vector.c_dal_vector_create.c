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
typedef  int /*<<< orphan*/  uint32_t ;
struct vector {int dummy; } ;
struct dc_context {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BREAK_TO_DEBUGGER () ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ dal_vector_construct (struct vector*,struct dc_context*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct vector*) ; 
 struct vector* kzalloc (int,int /*<<< orphan*/ ) ; 

struct vector *dal_vector_create(
	struct dc_context *ctx,
	uint32_t capacity,
	uint32_t struct_size)
{
	struct vector *vector = kzalloc(sizeof(struct vector), GFP_KERNEL);

	if (vector == NULL)
		return NULL;

	if (dal_vector_construct(vector, ctx, capacity, struct_size))
		return vector;

	BREAK_TO_DEBUGGER();
	kfree(vector);
	return NULL;
}