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
struct qdio_output_q {scalar_t__ use_cq; int /*<<< orphan*/ * aobs; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 

void qdio_disable_async_operation(struct qdio_output_q *q)
{
	kfree(q->aobs);
	q->aobs = NULL;
	q->use_cq = 0;
}