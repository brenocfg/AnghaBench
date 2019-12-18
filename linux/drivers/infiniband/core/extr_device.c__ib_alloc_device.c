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
struct ib_device {int /*<<< orphan*/  unregistration_work; int /*<<< orphan*/  unreg_completion; int /*<<< orphan*/  compat_devs_mutex; int /*<<< orphan*/  compat_devs; int /*<<< orphan*/  client_data_rwsem; int /*<<< orphan*/  client_data; int /*<<< orphan*/  unregistration_lock; int /*<<< orphan*/  event_handler_lock; int /*<<< orphan*/  event_handler_list; int /*<<< orphan*/  coredev; int /*<<< orphan*/ ** groups; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ WARN_ON (int) ; 
 int /*<<< orphan*/  XA_FLAGS_ALLOC ; 
 int /*<<< orphan*/  ib_dev_attr_group ; 
 int /*<<< orphan*/  ib_unregister_work ; 
 int /*<<< orphan*/  init_completion (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  init_net ; 
 int /*<<< orphan*/  init_rwsem (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct ib_device*) ; 
 struct ib_device* kzalloc (size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rdma_init_coredev (int /*<<< orphan*/ *,struct ib_device*,int /*<<< orphan*/ *) ; 
 scalar_t__ rdma_restrack_init (struct ib_device*) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xa_init_flags (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

struct ib_device *_ib_alloc_device(size_t size)
{
	struct ib_device *device;

	if (WARN_ON(size < sizeof(struct ib_device)))
		return NULL;

	device = kzalloc(size, GFP_KERNEL);
	if (!device)
		return NULL;

	if (rdma_restrack_init(device)) {
		kfree(device);
		return NULL;
	}

	device->groups[0] = &ib_dev_attr_group;
	rdma_init_coredev(&device->coredev, device, &init_net);

	INIT_LIST_HEAD(&device->event_handler_list);
	spin_lock_init(&device->event_handler_lock);
	mutex_init(&device->unregistration_lock);
	/*
	 * client_data needs to be alloc because we don't want our mark to be
	 * destroyed if the user stores NULL in the client data.
	 */
	xa_init_flags(&device->client_data, XA_FLAGS_ALLOC);
	init_rwsem(&device->client_data_rwsem);
	xa_init_flags(&device->compat_devs, XA_FLAGS_ALLOC);
	mutex_init(&device->compat_devs_mutex);
	init_completion(&device->unreg_completion);
	INIT_WORK(&device->unregistration_work, ib_unregister_work);

	return device;
}