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
struct TYPE_4__ {TYPE_1__ asq; } ;
struct i40e_hw {TYPE_2__ aq; } ;

/* Variables and functions */
 int /*<<< orphan*/  i40e_free_dma_mem (struct i40e_hw*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void i40e_free_adminq_asq(struct i40e_hw *hw)
{
	i40e_free_dma_mem(hw, &hw->aq.asq.desc_buf);
}