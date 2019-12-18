#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  desc_buf; } ;
struct TYPE_4__ {int num_arq_entries; TYPE_1__ arq; } ;
struct iavf_hw {TYPE_2__ aq; } ;
struct iavf_aq_desc {int dummy; } ;
typedef  enum iavf_status { ____Placeholder_iavf_status } iavf_status ;

/* Variables and functions */
 int /*<<< orphan*/  IAVF_ADMINQ_DESC_ALIGNMENT ; 
 int iavf_allocate_dma_mem (struct iavf_hw*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iavf_mem_arq_ring ; 

__attribute__((used)) static enum iavf_status iavf_alloc_adminq_arq_ring(struct iavf_hw *hw)
{
	enum iavf_status ret_code;

	ret_code = iavf_allocate_dma_mem(hw, &hw->aq.arq.desc_buf,
					 iavf_mem_arq_ring,
					 (hw->aq.num_arq_entries *
					 sizeof(struct iavf_aq_desc)),
					 IAVF_ADMINQ_DESC_ALIGNMENT);

	return ret_code;
}