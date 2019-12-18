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
typedef  int /*<<< orphan*/  u16 ;
struct TYPE_3__ {int desc_num; struct hclge_desc* desc; } ;
struct TYPE_4__ {int /*<<< orphan*/  last_status; TYPE_1__ csq; } ;
struct hclge_hw {TYPE_2__ cmq; } ;
struct hclge_desc {int /*<<< orphan*/  retval; int /*<<< orphan*/  opcode; } ;

/* Variables and functions */
 int hclge_cmd_convert_err_code (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hclge_is_special_opcode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  le16_to_cpu (int /*<<< orphan*/ ) ; 
 scalar_t__ likely (int) ; 

__attribute__((used)) static int hclge_cmd_check_retval(struct hclge_hw *hw, struct hclge_desc *desc,
				  int num, int ntc)
{
	u16 opcode, desc_ret;
	int handle;

	opcode = le16_to_cpu(desc[0].opcode);
	for (handle = 0; handle < num; handle++) {
		desc[handle] = hw->cmq.csq.desc[ntc];
		ntc++;
		if (ntc >= hw->cmq.csq.desc_num)
			ntc = 0;
	}
	if (likely(!hclge_is_special_opcode(opcode)))
		desc_ret = le16_to_cpu(desc[num - 1].retval);
	else
		desc_ret = le16_to_cpu(desc[0].retval);

	hw->cmq.last_status = desc_ret;

	return hclge_cmd_convert_err_code(desc_ret);
}