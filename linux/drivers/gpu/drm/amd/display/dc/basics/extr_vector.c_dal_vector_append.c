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
struct vector {int /*<<< orphan*/  count; } ;

/* Variables and functions */
 int dal_vector_insert_at (struct vector*,void const*,int /*<<< orphan*/ ) ; 

bool dal_vector_append(
	struct vector *vector,
	const void *item)
{
	return dal_vector_insert_at(vector, item, vector->count);
}