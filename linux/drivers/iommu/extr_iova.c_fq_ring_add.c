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
struct iova_fq {unsigned int tail; int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 unsigned int IOVA_FQ_SIZE ; 
 int /*<<< orphan*/  assert_spin_locked (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline unsigned fq_ring_add(struct iova_fq *fq)
{
	unsigned idx = fq->tail;

	assert_spin_locked(&fq->lock);

	fq->tail = (idx + 1) % IOVA_FQ_SIZE;

	return idx;
}