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
typedef  int u32 ;
struct mlx4_net_trans_rule_hw_ctrl {int dummy; } ;
struct _rule_hw {int size; } ;

/* Variables and functions */

__attribute__((used)) static u32 qp_attach_mbox_size(void *mbox)
{
	u32 size = sizeof(struct mlx4_net_trans_rule_hw_ctrl);
	struct _rule_hw  *rule_header;

	rule_header = (struct _rule_hw *)(mbox + size);

	while (rule_header->size) {
		size += rule_header->size * sizeof(u32);
		rule_header += 1;
	}
	return size;
}