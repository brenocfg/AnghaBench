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
struct efa_ibv_create_cq_resp {scalar_t__ q_mmap_key; int /*<<< orphan*/  q_mmap_size; } ;
struct efa_dev {int dummy; } ;
struct efa_cq {int /*<<< orphan*/  size; int /*<<< orphan*/  cpu_addr; int /*<<< orphan*/  ucontext; } ;

/* Variables and functions */
 int /*<<< orphan*/  EFA_MMAP_DMA_PAGE ; 
 scalar_t__ EFA_MMAP_INVALID ; 
 int ENOMEM ; 
 scalar_t__ mmap_entry_insert (struct efa_dev*,int /*<<< orphan*/ ,struct efa_cq*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  virt_to_phys (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int cq_mmap_entries_setup(struct efa_dev *dev, struct efa_cq *cq,
				 struct efa_ibv_create_cq_resp *resp)
{
	resp->q_mmap_size = cq->size;
	resp->q_mmap_key = mmap_entry_insert(dev, cq->ucontext, cq,
					     virt_to_phys(cq->cpu_addr),
					     cq->size, EFA_MMAP_DMA_PAGE);
	if (resp->q_mmap_key == EFA_MMAP_INVALID)
		return -ENOMEM;

	return 0;
}