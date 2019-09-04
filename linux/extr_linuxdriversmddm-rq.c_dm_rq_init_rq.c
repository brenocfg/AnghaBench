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
struct request_queue {int /*<<< orphan*/  rq_alloc_data; } ;
struct request {int dummy; } ;
typedef  int /*<<< orphan*/  gfp_t ;

/* Variables and functions */
 int __dm_rq_init_rq (int /*<<< orphan*/ ,struct request*) ; 

__attribute__((used)) static int dm_rq_init_rq(struct request_queue *q, struct request *rq, gfp_t gfp)
{
	return __dm_rq_init_rq(q->rq_alloc_data, rq);
}