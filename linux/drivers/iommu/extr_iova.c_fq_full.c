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
struct iova_fq {int tail; int head; int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int IOVA_FQ_SIZE ; 
 int /*<<< orphan*/  assert_spin_locked (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline bool fq_full(struct iova_fq *fq)
{
	assert_spin_locked(&fq->lock);
	return (((fq->tail + 1) % IOVA_FQ_SIZE) == fq->head);
}