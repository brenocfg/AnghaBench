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
struct nvmet_tcp_cmd {int dummy; } ;
struct nvmet_tcp_queue {int nr_cmds; struct nvmet_tcp_cmd connect; struct nvmet_tcp_cmd* cmds; } ;

/* Variables and functions */
 int /*<<< orphan*/  nvmet_tcp_finish_cmd (struct nvmet_tcp_cmd*) ; 
 scalar_t__ nvmet_tcp_need_data_in (struct nvmet_tcp_cmd*) ; 

__attribute__((used)) static void nvmet_tcp_uninit_data_in_cmds(struct nvmet_tcp_queue *queue)
{
	struct nvmet_tcp_cmd *cmd = queue->cmds;
	int i;

	for (i = 0; i < queue->nr_cmds; i++, cmd++) {
		if (nvmet_tcp_need_data_in(cmd))
			nvmet_tcp_finish_cmd(cmd);
	}

	if (!queue->nr_cmds && nvmet_tcp_need_data_in(&queue->connect)) {
		/* failed in connect */
		nvmet_tcp_finish_cmd(&queue->connect);
	}
}