#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct nvme_tcp_queue {TYPE_4__* ctrl; } ;
struct nvme_sgl_desc {int type; int /*<<< orphan*/  length; int /*<<< orphan*/  addr; } ;
struct TYPE_5__ {struct nvme_sgl_desc sgl; } ;
struct TYPE_6__ {TYPE_1__ dptr; } ;
struct nvme_command {TYPE_2__ common; } ;
struct TYPE_7__ {int /*<<< orphan*/  icdoff; } ;
struct TYPE_8__ {TYPE_3__ ctrl; } ;

/* Variables and functions */
 int NVME_SGL_FMT_DATA_DESC ; 
 int NVME_SGL_FMT_OFFSET ; 
 int /*<<< orphan*/  cpu_to_le32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpu_to_le64 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void nvme_tcp_set_sg_inline(struct nvme_tcp_queue *queue,
		struct nvme_command *c, u32 data_len)
{
	struct nvme_sgl_desc *sg = &c->common.dptr.sgl;

	sg->addr = cpu_to_le64(queue->ctrl->ctrl.icdoff);
	sg->length = cpu_to_le32(data_len);
	sg->type = (NVME_SGL_FMT_DATA_DESC << 4) | NVME_SGL_FMT_OFFSET;
}