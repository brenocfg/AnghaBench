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
struct hclge_desc {int /*<<< orphan*/  flag; } ;

/* Variables and functions */
 int HCLGE_CMD_FLAG_IN ; 
 int HCLGE_CMD_FLAG_NO_INTR ; 
 int HCLGE_CMD_FLAG_WR ; 
 int /*<<< orphan*/  cpu_to_le16 (int) ; 

void hclge_cmd_reuse_desc(struct hclge_desc *desc, bool is_read)
{
	desc->flag = cpu_to_le16(HCLGE_CMD_FLAG_NO_INTR | HCLGE_CMD_FLAG_IN);
	if (is_read)
		desc->flag |= cpu_to_le16(HCLGE_CMD_FLAG_WR);
	else
		desc->flag &= cpu_to_le16(~HCLGE_CMD_FLAG_WR);
}