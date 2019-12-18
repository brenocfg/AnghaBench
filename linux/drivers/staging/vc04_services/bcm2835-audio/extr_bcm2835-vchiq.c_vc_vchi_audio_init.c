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
struct service_creation {struct bcm2835_audio_instance* callback_param; int /*<<< orphan*/  callback; int /*<<< orphan*/  service_id; int /*<<< orphan*/  version; } ;
struct bcm2835_audio_instance {int /*<<< orphan*/  vchi_handle; int /*<<< orphan*/  dev; } ;
typedef  int /*<<< orphan*/  VCHI_INSTANCE_T ;

/* Variables and functions */
 int EPERM ; 
 int /*<<< orphan*/  VCHI_VERSION_EX (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VC_AUDIOSERV_MIN_VER ; 
 int /*<<< orphan*/  VC_AUDIOSERV_VER ; 
 int /*<<< orphan*/  VC_AUDIO_SERVER_NAME ; 
 int /*<<< orphan*/  audio_vchi_callback ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 int vchi_service_open (int /*<<< orphan*/ ,struct service_creation*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vchi_service_release (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
vc_vchi_audio_init(VCHI_INSTANCE_T vchi_instance,
		   struct bcm2835_audio_instance *instance)
{
	struct service_creation params = {
		.version		= VCHI_VERSION_EX(VC_AUDIOSERV_VER, VC_AUDIOSERV_MIN_VER),
		.service_id		= VC_AUDIO_SERVER_NAME,
		.callback		= audio_vchi_callback,
		.callback_param		= instance,
	};
	int status;

	/* Open the VCHI service connections */
	status = vchi_service_open(vchi_instance, &params,
				   &instance->vchi_handle);

	if (status) {
		dev_err(instance->dev,
			"failed to open VCHI service connection (status=%d)\n",
			status);
		return -EPERM;
	}

	/* Finished with the service for now */
	vchi_service_release(instance->vchi_handle);

	return 0;
}