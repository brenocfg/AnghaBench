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
struct qlcnic_cmd_args {int dummy; } ;
struct qlcnic_back_channel {int /*<<< orphan*/  queue_lock; int /*<<< orphan*/  async_cmd_list; } ;
struct qlcnic_async_cmd {int /*<<< orphan*/  list; struct qlcnic_cmd_args* cmd; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_ATOMIC ; 
 struct qlcnic_async_cmd* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static struct qlcnic_async_cmd *
qlcnic_sriov_alloc_async_cmd(struct qlcnic_back_channel *bc,
			     struct qlcnic_cmd_args *cmd)
{
	struct qlcnic_async_cmd *entry = NULL;

	entry = kzalloc(sizeof(*entry), GFP_ATOMIC);
	if (!entry)
		return NULL;

	entry->cmd = cmd;

	spin_lock(&bc->queue_lock);
	list_add_tail(&entry->list, &bc->async_cmd_list);
	spin_unlock(&bc->queue_lock);

	return entry;
}