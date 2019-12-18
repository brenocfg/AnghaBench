#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
typedef  int /*<<< orphan*/  u16 ;
struct qed_hwfn {struct qed_dev* cdev; } ;
struct qed_dev {TYPE_1__* fw_data; } ;
struct TYPE_2__ {int* modes_tree_buf; } ;

/* Variables and functions */
 int BIT (int) ; 
#define  INIT_MODE_OP_AND 130 
#define  INIT_MODE_OP_NOT 129 
#define  INIT_MODE_OP_OR 128 
 int MAX_INIT_MODE_OPS ; 

__attribute__((used)) static u8 qed_init_cmd_mode_match(struct qed_hwfn *p_hwfn,
				  u16 *p_offset, int modes)
{
	struct qed_dev *cdev = p_hwfn->cdev;
	const u8 *modes_tree_buf;
	u8 arg1, arg2, tree_val;

	modes_tree_buf = cdev->fw_data->modes_tree_buf;
	tree_val = modes_tree_buf[(*p_offset)++];
	switch (tree_val) {
	case INIT_MODE_OP_NOT:
		return qed_init_cmd_mode_match(p_hwfn, p_offset, modes) ^ 1;
	case INIT_MODE_OP_OR:
		arg1 = qed_init_cmd_mode_match(p_hwfn, p_offset, modes);
		arg2 = qed_init_cmd_mode_match(p_hwfn, p_offset, modes);
		return arg1 | arg2;
	case INIT_MODE_OP_AND:
		arg1 = qed_init_cmd_mode_match(p_hwfn, p_offset, modes);
		arg2 = qed_init_cmd_mode_match(p_hwfn, p_offset, modes);
		return arg1 & arg2;
	default:
		tree_val -= MAX_INIT_MODE_OPS;
		return (modes & BIT(tree_val)) ? 1 : 0;
	}
}