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
struct vector {scalar_t__ capacity; scalar_t__ count; int /*<<< orphan*/  container; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 

void dal_vector_destruct(
	struct vector *vector)
{
	kfree(vector->container);
	vector->count = 0;
	vector->capacity = 0;
}