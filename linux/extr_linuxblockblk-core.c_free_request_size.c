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
struct request_queue {int /*<<< orphan*/  (* exit_rq_fn ) (struct request_queue*,void*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (void*) ; 
 int /*<<< orphan*/  stub1 (struct request_queue*,void*) ; 

__attribute__((used)) static void free_request_size(void *element, void *data)
{
	struct request_queue *q = data;

	if (q->exit_rq_fn)
		q->exit_rq_fn(q, element);
	kfree(element);
}