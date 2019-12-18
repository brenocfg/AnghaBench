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
struct nvmet_tcp_cmd {TYPE_1__* queue; int /*<<< orphan*/  entry; } ;
struct TYPE_2__ {int /*<<< orphan*/  free_list; struct nvmet_tcp_cmd connect; } ;

/* Variables and functions */
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static inline void nvmet_tcp_put_cmd(struct nvmet_tcp_cmd *cmd)
{
	if (unlikely(cmd == &cmd->queue->connect))
		return;

	list_add_tail(&cmd->entry, &cmd->queue->free_list);
}