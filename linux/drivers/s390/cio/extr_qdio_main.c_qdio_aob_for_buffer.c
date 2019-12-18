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
typedef  scalar_t__ u64 ;
struct qdio_output_q {TYPE_1__* sbal_state; struct qaob** aobs; } ;
struct qaob {scalar_t__ user1; } ;
struct TYPE_2__ {scalar_t__ flags; scalar_t__ user; } ;

/* Variables and functions */
 int /*<<< orphan*/  WARN_ON_ONCE (unsigned long) ; 
 struct qaob* qdio_allocate_aob () ; 
 unsigned long virt_to_phys (struct qaob*) ; 

__attribute__((used)) static inline unsigned long qdio_aob_for_buffer(struct qdio_output_q *q,
					int bufnr)
{
	unsigned long phys_aob = 0;

	if (!q->aobs[bufnr]) {
		struct qaob *aob = qdio_allocate_aob();
		q->aobs[bufnr] = aob;
	}
	if (q->aobs[bufnr]) {
		q->aobs[bufnr]->user1 = (u64) q->sbal_state[bufnr].user;
		phys_aob = virt_to_phys(q->aobs[bufnr]);
		WARN_ON_ONCE(phys_aob & 0xFF);
	}

	q->sbal_state[bufnr].flags = 0;
	return phys_aob;
}