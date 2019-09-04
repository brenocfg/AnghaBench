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
typedef  scalar_t__ u32 ;
struct TYPE_3__ {scalar_t__ next_to_use; } ;
struct TYPE_4__ {TYPE_1__ crq; } ;
struct hclge_hw {TYPE_2__ cmq; } ;

/* Variables and functions */
 int /*<<< orphan*/  HCLGE_NIC_CRQ_TAIL_REG ; 
 scalar_t__ hclge_read_dev (struct hclge_hw*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool hclge_cmd_crq_empty(struct hclge_hw *hw)
{
	u32 tail = hclge_read_dev(hw, HCLGE_NIC_CRQ_TAIL_REG);

	return tail == hw->cmq.crq.next_to_use;
}