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
struct vector {int /*<<< orphan*/  struct_size; } ;

/* Variables and functions */
 int /*<<< orphan*/  BREAK_TO_DEBUGGER () ; 
 void* dal_vector_at_index (struct vector const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memmove (void*,void const*,int /*<<< orphan*/ ) ; 

void dal_vector_set_at_index(
	const struct vector *vector,
	const void *what,
	uint32_t index)
{
	void *where = dal_vector_at_index(vector, index);

	if (!where) {
		BREAK_TO_DEBUGGER();
		return;
	}
	memmove(
		where,
		what,
		vector->struct_size);
}