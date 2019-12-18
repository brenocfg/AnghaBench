#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u16 ;
struct nvmet_req {TYPE_3__* cmd; TYPE_1__* ns; } ;
struct TYPE_5__ {int opcode; } ;
struct TYPE_6__ {TYPE_2__ common; } ;
struct TYPE_4__ {int /*<<< orphan*/  readonly; } ;

/* Variables and functions */
 int /*<<< orphan*/  NVME_SC_NS_WRITE_PROTECTED ; 
#define  nvme_cmd_flush 129 
#define  nvme_cmd_read 128 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline u16 nvmet_io_cmd_check_access(struct nvmet_req *req)
{
	if (unlikely(req->ns->readonly)) {
		switch (req->cmd->common.opcode) {
		case nvme_cmd_read:
		case nvme_cmd_flush:
			break;
		default:
			return NVME_SC_NS_WRITE_PROTECTED;
		}
	}

	return 0;
}