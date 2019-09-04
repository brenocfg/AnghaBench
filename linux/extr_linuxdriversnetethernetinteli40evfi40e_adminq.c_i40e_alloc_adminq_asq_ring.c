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
struct TYPE_3__ {int /*<<< orphan*/  desc_buf; int /*<<< orphan*/  cmd_buf; } ;
struct TYPE_4__ {int num_asq_entries; TYPE_1__ asq; } ;
struct i40e_hw {TYPE_2__ aq; } ;
struct i40e_asq_cmd_details {int dummy; } ;
struct i40e_aq_desc {int dummy; } ;
typedef  scalar_t__ i40e_status ;

/* Variables and functions */
 int /*<<< orphan*/  I40E_ADMINQ_DESC_ALIGNMENT ; 
 scalar_t__ i40e_allocate_dma_mem (struct i40e_hw*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 scalar_t__ i40e_allocate_virt_mem (struct i40e_hw*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  i40e_free_dma_mem (struct i40e_hw*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  i40e_mem_atq_ring ; 

__attribute__((used)) static i40e_status i40e_alloc_adminq_asq_ring(struct i40e_hw *hw)
{
	i40e_status ret_code;

	ret_code = i40e_allocate_dma_mem(hw, &hw->aq.asq.desc_buf,
					 i40e_mem_atq_ring,
					 (hw->aq.num_asq_entries *
					 sizeof(struct i40e_aq_desc)),
					 I40E_ADMINQ_DESC_ALIGNMENT);
	if (ret_code)
		return ret_code;

	ret_code = i40e_allocate_virt_mem(hw, &hw->aq.asq.cmd_buf,
					  (hw->aq.num_asq_entries *
					  sizeof(struct i40e_asq_cmd_details)));
	if (ret_code) {
		i40e_free_dma_mem(hw, &hw->aq.asq.desc_buf);
		return ret_code;
	}

	return ret_code;
}