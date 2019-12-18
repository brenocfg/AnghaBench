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
typedef  size_t u8 ;
typedef  int /*<<< orphan*/  u32 ;
struct iwl_trans {size_t command_groups_size; struct iwl_hcmd_arr* command_groups; } ;
struct iwl_hcmd_names {char const* cmd_name; } ;
struct iwl_hcmd_arr {int /*<<< orphan*/  size; int /*<<< orphan*/  arr; } ;

/* Variables and functions */
 struct iwl_hcmd_names* bsearch (size_t*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,size_t,int /*<<< orphan*/ ) ; 
 size_t iwl_cmd_groupid (int /*<<< orphan*/ ) ; 
 size_t iwl_cmd_opcode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iwl_hcmd_names_cmp ; 

const char *iwl_get_cmd_string(struct iwl_trans *trans, u32 id)
{
	u8 grp, cmd;
	struct iwl_hcmd_names *ret;
	const struct iwl_hcmd_arr *arr;
	size_t size = sizeof(struct iwl_hcmd_names);

	grp = iwl_cmd_groupid(id);
	cmd = iwl_cmd_opcode(id);

	if (!trans->command_groups || grp >= trans->command_groups_size ||
	    !trans->command_groups[grp].arr)
		return "UNKNOWN";

	arr = &trans->command_groups[grp];
	ret = bsearch(&cmd, arr->arr, arr->size, size, iwl_hcmd_names_cmp);
	if (!ret)
		return "UNKNOWN";
	return ret->cmd_name;
}