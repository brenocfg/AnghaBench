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
struct mlx4_ib_wq {unsigned int head; unsigned int tail; unsigned int max_post; } ;
struct mlx4_ib_cq {int /*<<< orphan*/  lock; } ;
struct ib_cq {int dummy; } ;

/* Variables and functions */
 scalar_t__ likely (int) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 struct mlx4_ib_cq* to_mcq (struct ib_cq*) ; 

__attribute__((used)) static int mlx4_wq_overflow(struct mlx4_ib_wq *wq, int nreq, struct ib_cq *ib_cq)
{
	unsigned cur;
	struct mlx4_ib_cq *cq;

	cur = wq->head - wq->tail;
	if (likely(cur + nreq < wq->max_post))
		return 0;

	cq = to_mcq(ib_cq);
	spin_lock(&cq->lock);
	cur = wq->head - wq->tail;
	spin_unlock(&cq->lock);

	return cur + nreq >= wq->max_post;
}