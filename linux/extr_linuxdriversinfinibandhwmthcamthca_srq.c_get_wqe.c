#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {void* buf; } ;
struct TYPE_6__ {TYPE_2__* page_list; TYPE_1__ direct; } ;
struct mthca_srq {int wqe_shift; TYPE_3__ queue; scalar_t__ is_direct; } ;
struct TYPE_5__ {void* buf; } ;

/* Variables and functions */
 int PAGE_SHIFT ; 
 int PAGE_SIZE ; 

__attribute__((used)) static void *get_wqe(struct mthca_srq *srq, int n)
{
	if (srq->is_direct)
		return srq->queue.direct.buf + (n << srq->wqe_shift);
	else
		return srq->queue.page_list[(n << srq->wqe_shift) >> PAGE_SHIFT].buf +
			((n << srq->wqe_shift) & (PAGE_SIZE - 1));
}