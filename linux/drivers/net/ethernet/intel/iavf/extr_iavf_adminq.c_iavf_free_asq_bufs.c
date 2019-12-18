#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {scalar_t__ pa; } ;
struct TYPE_5__ {TYPE_4__* asq_bi; } ;
struct TYPE_6__ {int /*<<< orphan*/  dma_head; TYPE_4__ desc_buf; int /*<<< orphan*/  cmd_buf; TYPE_1__ r; } ;
struct TYPE_7__ {int num_asq_entries; TYPE_2__ asq; } ;
struct iavf_hw {TYPE_3__ aq; } ;

/* Variables and functions */
 int /*<<< orphan*/  iavf_free_dma_mem (struct iavf_hw*,TYPE_4__*) ; 
 int /*<<< orphan*/  iavf_free_virt_mem (struct iavf_hw*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void iavf_free_asq_bufs(struct iavf_hw *hw)
{
	int i;

	/* only unmap if the address is non-NULL */
	for (i = 0; i < hw->aq.num_asq_entries; i++)
		if (hw->aq.asq.r.asq_bi[i].pa)
			iavf_free_dma_mem(hw, &hw->aq.asq.r.asq_bi[i]);

	/* free the buffer info list */
	iavf_free_virt_mem(hw, &hw->aq.asq.cmd_buf);

	/* free the descriptor memory */
	iavf_free_dma_mem(hw, &hw->aq.asq.desc_buf);

	/* free the dma header */
	iavf_free_virt_mem(hw, &hw->aq.asq.dma_head);
}