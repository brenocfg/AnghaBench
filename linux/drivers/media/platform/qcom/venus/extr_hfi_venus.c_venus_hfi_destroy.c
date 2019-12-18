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
struct venus_hfi_device {int /*<<< orphan*/  lock; } ;
struct venus_core {int /*<<< orphan*/ * ops; int /*<<< orphan*/ * priv; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct venus_hfi_device*) ; 
 int /*<<< orphan*/  mutex_destroy (int /*<<< orphan*/ *) ; 
 struct venus_hfi_device* to_hfi_priv (struct venus_core*) ; 
 int /*<<< orphan*/  venus_interface_queues_release (struct venus_hfi_device*) ; 

void venus_hfi_destroy(struct venus_core *core)
{
	struct venus_hfi_device *hdev = to_hfi_priv(core);

	venus_interface_queues_release(hdev);
	mutex_destroy(&hdev->lock);
	kfree(hdev);
	core->priv = NULL;
	core->ops = NULL;
}