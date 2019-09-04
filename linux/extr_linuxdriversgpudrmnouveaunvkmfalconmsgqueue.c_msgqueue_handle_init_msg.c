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
typedef  int u32 ;
struct nvkm_subdev {int index; } ;
struct nvkm_msgqueue_hdr {int size; } ;
struct nvkm_msgqueue {TYPE_2__* func; struct nvkm_falcon* falcon; } ;
struct nvkm_falcon {struct nvkm_subdev* owner; } ;
struct TYPE_4__ {TYPE_1__* init_func; } ;
struct TYPE_3__ {int (* init_callback ) (struct nvkm_msgqueue*,struct nvkm_msgqueue_hdr*) ;} ;

/* Variables and functions */
 int ALIGN (int,int /*<<< orphan*/ ) ; 
 int EINVAL ; 
 int ENOSPC ; 
 int HDR_SIZE ; 
 int MSG_BUF_SIZE ; 
#define  NVKM_ENGINE_SEC2 129 
#define  NVKM_SUBDEV_PMU 128 
 int /*<<< orphan*/  QUEUE_ALIGNMENT ; 
 int /*<<< orphan*/  nvkm_error (struct nvkm_subdev const*,char*,int) ; 
 int nvkm_falcon_rd32 (struct nvkm_falcon*,int) ; 
 int /*<<< orphan*/  nvkm_falcon_read_dmem (struct nvkm_falcon*,int,int,int /*<<< orphan*/ ,struct nvkm_msgqueue_hdr*) ; 
 int /*<<< orphan*/  nvkm_falcon_wr32 (struct nvkm_falcon*,int,int) ; 
 int* nvkm_subdev_name ; 
 int stub1 (struct nvkm_msgqueue*,struct nvkm_msgqueue_hdr*) ; 

__attribute__((used)) static int
msgqueue_handle_init_msg(struct nvkm_msgqueue *priv,
			 struct nvkm_msgqueue_hdr *hdr)
{
	struct nvkm_falcon *falcon = priv->falcon;
	const struct nvkm_subdev *subdev = falcon->owner;
	u32 tail;
	u32 tail_reg;
	int ret;

	/*
	 * Of course the message queue registers vary depending on the falcon
	 * used...
	 */
	switch (falcon->owner->index) {
	case NVKM_SUBDEV_PMU:
		tail_reg = 0x4cc;
		break;
	case NVKM_ENGINE_SEC2:
		tail_reg = 0xa34;
		break;
	default:
		nvkm_error(subdev, "falcon %s unsupported for msgqueue!\n",
			   nvkm_subdev_name[falcon->owner->index]);
		return -EINVAL;
	}

	/*
	 * Read the message - queues are not initialized yet so we cannot rely
	 * on msg_queue_read()
	 */
	tail = nvkm_falcon_rd32(falcon, tail_reg);
	nvkm_falcon_read_dmem(falcon, tail, HDR_SIZE, 0, hdr);

	if (hdr->size > MSG_BUF_SIZE) {
		nvkm_error(subdev, "message too big (%d bytes)\n", hdr->size);
		return -ENOSPC;
	}

	nvkm_falcon_read_dmem(falcon, tail + HDR_SIZE, hdr->size - HDR_SIZE, 0,
			      (hdr + 1));

	tail += ALIGN(hdr->size, QUEUE_ALIGNMENT);
	nvkm_falcon_wr32(falcon, tail_reg, tail);

	ret = priv->func->init_func->init_callback(priv, hdr);
	if (ret)
		return ret;

	return 0;
}