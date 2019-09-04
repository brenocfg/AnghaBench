#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct nicvf {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  base; } ;
struct cmp_queue {TYPE_1__ dmem; } ;

/* Variables and functions */
 int /*<<< orphan*/  nicvf_free_q_desc_mem (struct nicvf*,TYPE_1__*) ; 

__attribute__((used)) static void nicvf_free_cmp_queue(struct nicvf *nic, struct cmp_queue *cq)
{
	if (!cq)
		return;
	if (!cq->dmem.base)
		return;

	nicvf_free_q_desc_mem(nic, &cq->dmem);
}