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
struct vsp1_pre_ext_dl_body {int dummy; } ;
struct vsp1_dl_ext_cmd {size_t size; int num_cmds; int /*<<< orphan*/  free; scalar_t__ dma; scalar_t__ data_dma; struct vsp1_dl_ext_cmd* mem; struct vsp1_dl_ext_cmd* data; scalar_t__ cmd_dma; struct vsp1_dl_ext_cmd* cmds; int /*<<< orphan*/  opcode; struct vsp1_dl_ext_cmd* pool; int /*<<< orphan*/  lock; } ;
struct vsp1_dl_cmd_pool {size_t size; int num_cmds; int /*<<< orphan*/  free; scalar_t__ dma; scalar_t__ data_dma; struct vsp1_dl_cmd_pool* mem; struct vsp1_dl_cmd_pool* data; scalar_t__ cmd_dma; struct vsp1_dl_cmd_pool* cmds; int /*<<< orphan*/  opcode; struct vsp1_dl_cmd_pool* pool; int /*<<< orphan*/  lock; } ;
struct vsp1_device {int /*<<< orphan*/  bus_master; } ;
typedef  enum vsp1_extcmd_type { ____Placeholder_vsp1_extcmd_type } vsp1_extcmd_type ;
struct TYPE_2__ {int body_size; int /*<<< orphan*/  opcode; } ;

/* Variables and functions */
 size_t ALIGN (size_t,int) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 struct vsp1_dl_ext_cmd* dma_alloc_wc (int /*<<< orphan*/ ,size_t,scalar_t__*,int /*<<< orphan*/ ) ; 
 struct vsp1_dl_ext_cmd* kcalloc (unsigned int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct vsp1_dl_ext_cmd*) ; 
 struct vsp1_dl_ext_cmd* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 TYPE_1__* vsp1_extended_commands ; 

__attribute__((used)) static struct vsp1_dl_cmd_pool *
vsp1_dl_cmd_pool_create(struct vsp1_device *vsp1, enum vsp1_extcmd_type type,
			unsigned int num_cmds)
{
	struct vsp1_dl_cmd_pool *pool;
	unsigned int i;
	size_t cmd_size;

	pool = kzalloc(sizeof(*pool), GFP_KERNEL);
	if (!pool)
		return NULL;

	spin_lock_init(&pool->lock);
	INIT_LIST_HEAD(&pool->free);

	pool->cmds = kcalloc(num_cmds, sizeof(*pool->cmds), GFP_KERNEL);
	if (!pool->cmds) {
		kfree(pool);
		return NULL;
	}

	cmd_size = sizeof(struct vsp1_pre_ext_dl_body) +
		   vsp1_extended_commands[type].body_size;
	cmd_size = ALIGN(cmd_size, 16);

	pool->size = cmd_size * num_cmds;
	pool->mem = dma_alloc_wc(vsp1->bus_master, pool->size, &pool->dma,
				 GFP_KERNEL);
	if (!pool->mem) {
		kfree(pool->cmds);
		kfree(pool);
		return NULL;
	}

	for (i = 0; i < num_cmds; ++i) {
		struct vsp1_dl_ext_cmd *cmd = &pool->cmds[i];
		size_t cmd_offset = i * cmd_size;
		/* data_offset must be 16 byte aligned for DMA. */
		size_t data_offset = sizeof(struct vsp1_pre_ext_dl_body) +
				     cmd_offset;

		cmd->pool = pool;
		cmd->opcode = vsp1_extended_commands[type].opcode;

		/*
		 * TODO: Auto-disp can utilise more than one extended body
		 * command per cmd.
		 */
		cmd->num_cmds = 1;
		cmd->cmds = pool->mem + cmd_offset;
		cmd->cmd_dma = pool->dma + cmd_offset;

		cmd->data = pool->mem + data_offset;
		cmd->data_dma = pool->dma + data_offset;

		list_add_tail(&cmd->free, &pool->free);
	}

	return pool;
}