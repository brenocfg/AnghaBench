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
struct TYPE_4__ {TYPE_1__ arq; } ;
struct iavf_hw {TYPE_2__ aq; } ;

/* Variables and functions */
 int /*<<< orphan*/  iavf_free_dma_mem (struct iavf_hw*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void iavf_free_adminq_arq(struct iavf_hw *hw)
{
	iavf_free_dma_mem(hw, &hw->aq.arq.desc_buf);
}