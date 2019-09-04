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
typedef  union rdma_cqe {int dummy; } rdma_cqe ;
struct qedr_cq {union rdma_cqe* latest_cqe; } ;

/* Variables and functions */

__attribute__((used)) static union rdma_cqe *get_cqe(struct qedr_cq *cq)
{
	return cq->latest_cqe;
}