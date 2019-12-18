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
struct TYPE_2__ {int /*<<< orphan*/  cmd; } ;
struct nvmet_tcp_cmd {int /*<<< orphan*/  rbytes_done; scalar_t__ pdu_len; TYPE_1__ req; } ;

/* Variables and functions */
 scalar_t__ nvme_is_write (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline bool nvmet_tcp_has_inline_data(struct nvmet_tcp_cmd *cmd)
{
	return nvme_is_write(cmd->req.cmd) && cmd->pdu_len &&
		!cmd->rbytes_done;
}