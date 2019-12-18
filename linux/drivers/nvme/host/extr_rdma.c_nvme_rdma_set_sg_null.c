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
struct nvme_keyed_sgl_desc {int type; int /*<<< orphan*/  key; int /*<<< orphan*/  length; scalar_t__ addr; } ;
struct TYPE_3__ {struct nvme_keyed_sgl_desc ksgl; } ;
struct TYPE_4__ {TYPE_1__ dptr; } ;
struct nvme_command {TYPE_2__ common; } ;

/* Variables and functions */
 int NVME_KEY_SGL_FMT_DATA_DESC ; 
 int /*<<< orphan*/  put_unaligned_le24 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  put_unaligned_le32 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int nvme_rdma_set_sg_null(struct nvme_command *c)
{
	struct nvme_keyed_sgl_desc *sg = &c->common.dptr.ksgl;

	sg->addr = 0;
	put_unaligned_le24(0, sg->length);
	put_unaligned_le32(0, sg->key);
	sg->type = NVME_KEY_SGL_FMT_DATA_DESC << 4;
	return 0;
}