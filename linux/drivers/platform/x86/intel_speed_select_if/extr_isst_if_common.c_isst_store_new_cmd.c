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
typedef  void* u32 ;
struct isst_cmd {int cmd; int mbox_cmd_type; int /*<<< orphan*/  hnode; void* data; void* param; void* cpu; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  hash_add (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  isst_hash ; 
 struct isst_cmd* kmalloc (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int isst_store_new_cmd(int cmd, u32 cpu, int mbox_cmd_type, u32 param,
			      u32 data)
{
	struct isst_cmd *sst_cmd;

	sst_cmd = kmalloc(sizeof(*sst_cmd), GFP_KERNEL);
	if (!sst_cmd)
		return -ENOMEM;

	sst_cmd->cpu = cpu;
	sst_cmd->cmd = cmd;
	sst_cmd->mbox_cmd_type = mbox_cmd_type;
	sst_cmd->param = param;
	sst_cmd->data = data;

	hash_add(isst_hash, &sst_cmd->hnode, sst_cmd->cmd);

	return 0;
}