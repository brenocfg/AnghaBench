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
typedef  scalar_t__ u32 ;
struct nvkm_subdev {int dummy; } ;
struct nvkm_msgqueue_msg {int dummy; } ;
struct nvkm_msgqueue_hdr {int dummy; } ;
struct nvkm_msgqueue {int /*<<< orphan*/  init_done; TYPE_1__* falcon; } ;
struct TYPE_2__ {struct nvkm_subdev* owner; } ;

/* Variables and functions */
 int /*<<< orphan*/  complete_all (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nvkm_debug (struct nvkm_subdev const*,char*) ; 
 int /*<<< orphan*/  nvkm_error (struct nvkm_subdev const*,char*,scalar_t__) ; 

__attribute__((used)) static void
acr_init_wpr_callback(struct nvkm_msgqueue *queue,
		      struct nvkm_msgqueue_hdr *hdr)
{
	struct {
		struct nvkm_msgqueue_msg base;
		u32 error_code;
	} *msg = (void *)hdr;
	const struct nvkm_subdev *subdev = queue->falcon->owner;

	if (msg->error_code) {
		nvkm_error(subdev, "ACR WPR init failure: %d\n",
			   msg->error_code);
		return;
	}

	nvkm_debug(subdev, "ACR WPR init complete\n");
	complete_all(&queue->init_done);
}