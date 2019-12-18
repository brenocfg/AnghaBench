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
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u32 ;
struct nvkm_msgqueue {int dummy; } ;
struct nvkm_falcon {TYPE_1__* owner; } ;
struct nvkm_device {int dummy; } ;
typedef  int /*<<< orphan*/  buf ;
struct TYPE_2__ {int /*<<< orphan*/  index; struct nvkm_device* device; } ;

/* Variables and functions */
 int NVKM_MSGQUEUE_CMDLINE_SIZE ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  nvkm_falcon_load_dmem (struct nvkm_falcon*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nvkm_falcon_start (struct nvkm_falcon*) ; 
 int /*<<< orphan*/  nvkm_falcon_wr32 (struct nvkm_falcon*,int,int) ; 
 int /*<<< orphan*/  nvkm_mc_intr_mask (struct nvkm_device*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  nvkm_msgqueue_reinit (struct nvkm_msgqueue*) ; 
 int /*<<< orphan*/  nvkm_msgqueue_write_cmdline (struct nvkm_msgqueue*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
acr_ls_msgqueue_post_run(struct nvkm_msgqueue *queue,
			 struct nvkm_falcon *falcon, u32 addr_args)
{
	struct nvkm_device *device = falcon->owner->device;
	u8 buf[NVKM_MSGQUEUE_CMDLINE_SIZE];

	memset(buf, 0, sizeof(buf));
	nvkm_msgqueue_write_cmdline(queue, buf);
	nvkm_falcon_load_dmem(falcon, buf, addr_args, sizeof(buf), 0);
	/* rearm the queue so it will wait for the init message */
	nvkm_msgqueue_reinit(queue);

	/* Enable interrupts */
	nvkm_falcon_wr32(falcon, 0x10, 0xff);
	nvkm_mc_intr_mask(device, falcon->owner->index, true);

	/* Start LS firmware on boot falcon */
	nvkm_falcon_start(falcon);

	return 0;
}