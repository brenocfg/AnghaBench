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
struct hns_roce_srq {int wqe_shift; int /*<<< orphan*/  buf; } ;

/* Variables and functions */
 void* hns_roce_buf_offset (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void *get_srq_wqe(struct hns_roce_srq *srq, int n)
{
	return hns_roce_buf_offset(&srq->buf, n << srq->wqe_shift);
}