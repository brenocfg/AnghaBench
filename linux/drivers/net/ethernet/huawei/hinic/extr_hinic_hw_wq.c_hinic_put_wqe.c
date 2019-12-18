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
struct hinic_wq {int wqebb_size_shift; int /*<<< orphan*/  delta; int /*<<< orphan*/  cons_idx; int /*<<< orphan*/  wqebb_size; } ;

/* Variables and functions */
 int ALIGN (unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  atomic_add (int,int /*<<< orphan*/ *) ; 

void hinic_put_wqe(struct hinic_wq *wq, unsigned int wqe_size)
{
	int num_wqebbs = ALIGN(wqe_size, wq->wqebb_size)
			>> wq->wqebb_size_shift;

	atomic_add(num_wqebbs, &wq->cons_idx);

	atomic_add(num_wqebbs, &wq->delta);
}