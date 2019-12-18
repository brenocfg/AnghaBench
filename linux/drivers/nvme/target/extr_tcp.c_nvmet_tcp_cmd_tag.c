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
typedef  struct nvmet_tcp_cmd* u16 ;
struct nvmet_tcp_queue {int cmds; } ;
struct nvmet_tcp_cmd {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static inline u16 nvmet_tcp_cmd_tag(struct nvmet_tcp_queue *queue,
		struct nvmet_tcp_cmd *cmd)
{
	return cmd - queue->cmds;
}