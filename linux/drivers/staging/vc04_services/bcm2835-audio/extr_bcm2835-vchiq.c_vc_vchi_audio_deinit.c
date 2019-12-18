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
struct bcm2835_audio_instance {int /*<<< orphan*/  vchi_mutex; int /*<<< orphan*/  dev; int /*<<< orphan*/  vchi_handle; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int vchi_service_close (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vchi_service_use (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void vc_vchi_audio_deinit(struct bcm2835_audio_instance *instance)
{
	int status;

	mutex_lock(&instance->vchi_mutex);
	vchi_service_use(instance->vchi_handle);

	/* Close all VCHI service connections */
	status = vchi_service_close(instance->vchi_handle);
	if (status) {
		dev_err(instance->dev,
			"failed to close VCHI service connection (status=%d)\n",
			status);
	}

	mutex_unlock(&instance->vchi_mutex);
}