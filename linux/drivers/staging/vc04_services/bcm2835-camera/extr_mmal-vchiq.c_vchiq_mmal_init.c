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
struct vchiq_mmal_instance {int /*<<< orphan*/  bulk_scratch; int /*<<< orphan*/  bulk_wq; int /*<<< orphan*/  handle; int /*<<< orphan*/  context_map; int /*<<< orphan*/  context_map_lock; int /*<<< orphan*/  vchiq_mutex; } ;
struct service_creation {struct vchiq_mmal_instance* callback_param; int /*<<< orphan*/  callback; int /*<<< orphan*/  service_id; int /*<<< orphan*/  version; } ;
struct mmal_port {int dummy; } ;
struct mmal_msg_header {int dummy; } ;
struct mmal_msg {int dummy; } ;
typedef  int /*<<< orphan*/  VCHI_INSTANCE_T ;

/* Variables and functions */
 int /*<<< orphan*/  BUILD_BUG_ON (int) ; 
 int EIO ; 
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int MMAL_MSG_MAX_SIZE ; 
 int /*<<< orphan*/  PAGE_SIZE ; 
 int /*<<< orphan*/  VCHI_VERSION_EX (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VC_MMAL_MIN_VER ; 
 int /*<<< orphan*/  VC_MMAL_SERVER_NAME ; 
 int /*<<< orphan*/  VC_MMAL_VER ; 
 int /*<<< orphan*/  WQ_MEM_RECLAIM ; 
 int /*<<< orphan*/  alloc_ordered_workqueue (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  destroy_workqueue (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  idr_init_base (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  kfree (struct vchiq_mmal_instance*) ; 
 struct vchiq_mmal_instance* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_err (char*,int) ; 
 int /*<<< orphan*/  service_callback ; 
 int vchi_connect (int /*<<< orphan*/ ) ; 
 int vchi_initialise (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vchi_service_close (int /*<<< orphan*/ ) ; 
 int vchi_service_open (int /*<<< orphan*/ ,struct service_creation*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vchi_service_release (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vfree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vmalloc (int /*<<< orphan*/ ) ; 

int vchiq_mmal_init(struct vchiq_mmal_instance **out_instance)
{
	int status;
	struct vchiq_mmal_instance *instance;
	static VCHI_INSTANCE_T vchi_instance;
	struct service_creation params = {
		.version		= VCHI_VERSION_EX(VC_MMAL_VER, VC_MMAL_MIN_VER),
		.service_id		= VC_MMAL_SERVER_NAME,
		.callback		= service_callback,
		.callback_param		= NULL,
	};

	/* compile time checks to ensure structure size as they are
	 * directly (de)serialised from memory.
	 */

	/* ensure the header structure has packed to the correct size */
	BUILD_BUG_ON(sizeof(struct mmal_msg_header) != 24);

	/* ensure message structure does not exceed maximum length */
	BUILD_BUG_ON(sizeof(struct mmal_msg) > MMAL_MSG_MAX_SIZE);

	/* mmal port struct is correct size */
	BUILD_BUG_ON(sizeof(struct mmal_port) != 64);

	/* create a vchi instance */
	status = vchi_initialise(&vchi_instance);
	if (status) {
		pr_err("Failed to initialise VCHI instance (status=%d)\n",
		       status);
		return -EIO;
	}

	status = vchi_connect(vchi_instance);
	if (status) {
		pr_err("Failed to connect VCHI instance (status=%d)\n", status);
		return -EIO;
	}

	instance = kzalloc(sizeof(*instance), GFP_KERNEL);

	if (!instance)
		return -ENOMEM;

	mutex_init(&instance->vchiq_mutex);

	instance->bulk_scratch = vmalloc(PAGE_SIZE);

	mutex_init(&instance->context_map_lock);
	idr_init_base(&instance->context_map, 1);

	params.callback_param = instance;

	instance->bulk_wq = alloc_ordered_workqueue("mmal-vchiq",
						    WQ_MEM_RECLAIM);
	if (!instance->bulk_wq)
		goto err_free;

	status = vchi_service_open(vchi_instance, &params, &instance->handle);
	if (status) {
		pr_err("Failed to open VCHI service connection (status=%d)\n",
		       status);
		goto err_close_services;
	}

	vchi_service_release(instance->handle);

	*out_instance = instance;

	return 0;

err_close_services:
	vchi_service_close(instance->handle);
	destroy_workqueue(instance->bulk_wq);
err_free:
	vfree(instance->bulk_scratch);
	kfree(instance);
	return -ENODEV;
}