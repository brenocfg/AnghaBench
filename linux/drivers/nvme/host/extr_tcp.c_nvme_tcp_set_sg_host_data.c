#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct nvme_sgl_desc {int type; int /*<<< orphan*/  length; scalar_t__ addr; } ;
struct TYPE_3__ {struct nvme_sgl_desc sgl; } ;
struct TYPE_4__ {TYPE_1__ dptr; } ;
struct nvme_command {TYPE_2__ common; } ;

/* Variables and functions */
 int NVME_SGL_FMT_TRANSPORT_A ; 
 int NVME_TRANSPORT_SGL_DATA_DESC ; 
 int /*<<< orphan*/  cpu_to_le32 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void nvme_tcp_set_sg_host_data(struct nvme_command *c,
		u32 data_len)
{
	struct nvme_sgl_desc *sg = &c->common.dptr.sgl;

	sg->addr = 0;
	sg->length = cpu_to_le32(data_len);
	sg->type = (NVME_TRANSPORT_SGL_DATA_DESC << 4) |
			NVME_SGL_FMT_TRANSPORT_A;
}