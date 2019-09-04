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
struct ib_uverbs_cmd_hdr {int command; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  EOPNOTSUPP ; 
 int IB_USER_VERBS_CMD_COMMAND_MASK ; 
 int IB_USER_VERBS_CMD_FLAG_EXTENDED ; 
 int /*<<< orphan*/  verify_command_idx (int,int) ; 

__attribute__((used)) static ssize_t process_hdr(struct ib_uverbs_cmd_hdr *hdr,
			   u32 *command, bool *extended)
{
	if (hdr->command & ~(u32)(IB_USER_VERBS_CMD_FLAG_EXTENDED |
				   IB_USER_VERBS_CMD_COMMAND_MASK))
		return -EINVAL;

	*command = hdr->command & IB_USER_VERBS_CMD_COMMAND_MASK;
	*extended = hdr->command & IB_USER_VERBS_CMD_FLAG_EXTENDED;

	if (!verify_command_idx(*command, *extended))
		return -EOPNOTSUPP;

	return 0;
}