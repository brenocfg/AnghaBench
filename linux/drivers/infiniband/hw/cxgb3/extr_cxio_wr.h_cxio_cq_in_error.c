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
struct t3_cq_status_page {int cq_err; } ;
struct t3_cq {int size_log2; int /*<<< orphan*/ * queue; } ;

/* Variables and functions */

__attribute__((used)) static inline int cxio_cq_in_error(struct t3_cq *cq)
{
	return ((struct t3_cq_status_page *)
		&cq->queue[1 << cq->size_log2])->cq_err;
}