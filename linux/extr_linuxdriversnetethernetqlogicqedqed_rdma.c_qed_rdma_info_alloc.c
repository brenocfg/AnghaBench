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
struct qed_rdma_info {int /*<<< orphan*/  lock; } ;
struct qed_hwfn {struct qed_rdma_info* p_rdma_info; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 struct qed_rdma_info* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

int qed_rdma_info_alloc(struct qed_hwfn *p_hwfn)
{
	struct qed_rdma_info *p_rdma_info;

	p_rdma_info = kzalloc(sizeof(*p_rdma_info), GFP_KERNEL);
	if (!p_rdma_info)
		return -ENOMEM;

	spin_lock_init(&p_rdma_info->lock);

	p_hwfn->p_rdma_info = p_rdma_info;
	return 0;
}