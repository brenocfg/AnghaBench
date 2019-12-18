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
struct TYPE_2__ {int /*<<< orphan*/  sg; } ;
struct nvmet_tcp_cmd {TYPE_1__ req; int /*<<< orphan*/  iov; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nvmet_req_uninit (TYPE_1__*) ; 
 int /*<<< orphan*/  nvmet_tcp_unmap_pdu_iovec (struct nvmet_tcp_cmd*) ; 
 int /*<<< orphan*/  sgl_free (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void nvmet_tcp_finish_cmd(struct nvmet_tcp_cmd *cmd)
{
	nvmet_req_uninit(&cmd->req);
	nvmet_tcp_unmap_pdu_iovec(cmd);
	kfree(cmd->iov);
	sgl_free(cmd->req.sg);
}