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
struct t4_cq {size_t cidx; int /*<<< orphan*/ * queue; scalar_t__ sw_in_use; } ;

/* Variables and functions */
 scalar_t__ t4_valid_cqe (struct t4_cq*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline int t4_cq_notempty(struct t4_cq *cq)
{
	return cq->sw_in_use || t4_valid_cqe(cq, &cq->queue[cq->cidx]);
}