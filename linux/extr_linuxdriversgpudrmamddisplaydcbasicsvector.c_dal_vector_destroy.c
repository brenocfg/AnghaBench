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
struct vector {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  dal_vector_destruct (struct vector*) ; 
 int /*<<< orphan*/  kfree (struct vector*) ; 

void dal_vector_destroy(
	struct vector **vector)
{
	if (vector == NULL || *vector == NULL)
		return;
	dal_vector_destruct(*vector);
	kfree(*vector);
	*vector = NULL;
}