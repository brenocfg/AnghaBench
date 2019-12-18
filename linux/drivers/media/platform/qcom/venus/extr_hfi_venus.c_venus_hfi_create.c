#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct venus_hfi_device {int suspended; struct venus_core* core; int /*<<< orphan*/  lock; } ;
struct venus_core {int core_caps; int /*<<< orphan*/ * ops; struct venus_hfi_device* priv; } ;

/* Variables and functions */
 int DEC_MULTI_STREAM_CAPABILITY ; 
 int ENC_DEINTERLACE_CAPABILITY ; 
 int ENC_ROTATION_CAPABILITY ; 
 int ENC_SCALING_CAPABILITY ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  kfree (struct venus_hfi_device*) ; 
 struct venus_hfi_device* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  venus_hfi_ops ; 
 int venus_interface_queues_init (struct venus_hfi_device*) ; 

int venus_hfi_create(struct venus_core *core)
{
	struct venus_hfi_device *hdev;
	int ret;

	hdev = kzalloc(sizeof(*hdev), GFP_KERNEL);
	if (!hdev)
		return -ENOMEM;

	mutex_init(&hdev->lock);

	hdev->core = core;
	hdev->suspended = true;
	core->priv = hdev;
	core->ops = &venus_hfi_ops;
	core->core_caps = ENC_ROTATION_CAPABILITY | ENC_SCALING_CAPABILITY |
			  ENC_DEINTERLACE_CAPABILITY |
			  DEC_MULTI_STREAM_CAPABILITY;

	ret = venus_interface_queues_init(hdev);
	if (ret)
		goto err_kfree;

	return 0;

err_kfree:
	kfree(hdev);
	core->priv = NULL;
	core->ops = NULL;
	return ret;
}