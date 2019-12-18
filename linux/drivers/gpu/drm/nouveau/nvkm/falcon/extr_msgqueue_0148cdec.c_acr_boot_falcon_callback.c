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
typedef  size_t u32 ;
struct nvkm_subdev {int dummy; } ;
struct nvkm_msgqueue_msg {int dummy; } ;
struct nvkm_msgqueue_hdr {int dummy; } ;
struct nvkm_msgqueue {TYPE_1__* falcon; } ;
struct TYPE_2__ {struct nvkm_subdev* owner; } ;

/* Variables and functions */
 size_t NVKM_SECBOOT_FALCON_END ; 
 int /*<<< orphan*/  nvkm_debug (struct nvkm_subdev const*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nvkm_error (struct nvkm_subdev const*,char*,...) ; 
 int /*<<< orphan*/ * nvkm_secboot_falcon_name ; 

__attribute__((used)) static void
acr_boot_falcon_callback(struct nvkm_msgqueue *priv,
			 struct nvkm_msgqueue_hdr *hdr)
{
	struct acr_bootstrap_falcon_msg {
		struct nvkm_msgqueue_msg base;

		u32 error_code;
		u32 falcon_id;
	} *msg = (void *)hdr;
	const struct nvkm_subdev *subdev = priv->falcon->owner;
	u32 falcon_id = msg->falcon_id;

	if (msg->error_code) {
		nvkm_error(subdev, "in bootstrap falcon callback:\n");
		nvkm_error(subdev, "expected error code 0x%x\n",
			   msg->error_code);
		return;
	}

	if (falcon_id >= NVKM_SECBOOT_FALCON_END) {
		nvkm_error(subdev, "in bootstrap falcon callback:\n");
		nvkm_error(subdev, "invalid falcon ID 0x%x\n", falcon_id);
		return;
	}

	nvkm_debug(subdev, "%s booted\n", nvkm_secboot_falcon_name[falcon_id]);
}