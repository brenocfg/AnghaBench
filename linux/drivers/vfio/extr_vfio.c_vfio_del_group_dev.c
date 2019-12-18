#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct vfio_unbound_dev {int /*<<< orphan*/  unbound_next; struct device* dev; } ;
struct vfio_group {int /*<<< orphan*/  container; int /*<<< orphan*/  container_q; int /*<<< orphan*/  device_list; int /*<<< orphan*/  unbound_lock; int /*<<< orphan*/  unbound_list; } ;
struct vfio_device {TYPE_1__* ops; void* device_data; struct vfio_group* group; } ;
struct device {int dummy; } ;
struct TYPE_8__ {int /*<<< orphan*/  comm; } ;
struct TYPE_7__ {int /*<<< orphan*/  release_q; } ;
struct TYPE_6__ {int /*<<< orphan*/  (* request ) (void*,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  DEFINE_WAIT_FUNC (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int HZ ; 
 int /*<<< orphan*/  TASK_INTERRUPTIBLE ; 
 int /*<<< orphan*/  TASK_UNINTERRUPTIBLE ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  add_wait_queue (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 TYPE_3__* current ; 
 struct vfio_device* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  dev_warn (struct device*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct vfio_unbound_dev* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  remove_wait_queue (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ signal_pending (TYPE_3__*) ; 
 int /*<<< orphan*/  stub1 (void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  task_pid_nr (TYPE_3__*) ; 
 TYPE_2__ vfio ; 
 int /*<<< orphan*/  vfio_device_put (struct vfio_device*) ; 
 int /*<<< orphan*/  vfio_group_get (struct vfio_group*) ; 
 struct vfio_device* vfio_group_get_device (struct vfio_group*,struct device*) ; 
 int /*<<< orphan*/  vfio_group_put (struct vfio_group*) ; 
 int /*<<< orphan*/  wait ; 
 int /*<<< orphan*/  wait_event (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  wait_woken (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  woken_wake_function ; 

void *vfio_del_group_dev(struct device *dev)
{
	DEFINE_WAIT_FUNC(wait, woken_wake_function);
	struct vfio_device *device = dev_get_drvdata(dev);
	struct vfio_group *group = device->group;
	void *device_data = device->device_data;
	struct vfio_unbound_dev *unbound;
	unsigned int i = 0;
	bool interrupted = false;

	/*
	 * The group exists so long as we have a device reference.  Get
	 * a group reference and use it to scan for the device going away.
	 */
	vfio_group_get(group);

	/*
	 * When the device is removed from the group, the group suddenly
	 * becomes non-viable; the device has a driver (until the unbind
	 * completes), but it's not present in the group.  This is bad news
	 * for any external users that need to re-acquire a group reference
	 * in order to match and release their existing reference.  To
	 * solve this, we track such devices on the unbound_list to bridge
	 * the gap until they're fully unbound.
	 */
	unbound = kzalloc(sizeof(*unbound), GFP_KERNEL);
	if (unbound) {
		unbound->dev = dev;
		mutex_lock(&group->unbound_lock);
		list_add(&unbound->unbound_next, &group->unbound_list);
		mutex_unlock(&group->unbound_lock);
	}
	WARN_ON(!unbound);

	vfio_device_put(device);

	/*
	 * If the device is still present in the group after the above
	 * 'put', then it is in use and we need to request it from the
	 * bus driver.  The driver may in turn need to request the
	 * device from the user.  We send the request on an arbitrary
	 * interval with counter to allow the driver to take escalating
	 * measures to release the device if it has the ability to do so.
	 */
	add_wait_queue(&vfio.release_q, &wait);

	do {
		device = vfio_group_get_device(group, dev);
		if (!device)
			break;

		if (device->ops->request)
			device->ops->request(device_data, i++);

		vfio_device_put(device);

		if (interrupted) {
			wait_woken(&wait, TASK_UNINTERRUPTIBLE, HZ * 10);
		} else {
			wait_woken(&wait, TASK_INTERRUPTIBLE, HZ * 10);
			if (signal_pending(current)) {
				interrupted = true;
				dev_warn(dev,
					 "Device is currently in use, task"
					 " \"%s\" (%d) "
					 "blocked until device is released",
					 current->comm, task_pid_nr(current));
			}
		}

	} while (1);

	remove_wait_queue(&vfio.release_q, &wait);
	/*
	 * In order to support multiple devices per group, devices can be
	 * plucked from the group while other devices in the group are still
	 * in use.  The container persists with this group and those remaining
	 * devices still attached.  If the user creates an isolation violation
	 * by binding this device to another driver while the group is still in
	 * use, that's their fault.  However, in the case of removing the last,
	 * or potentially the only, device in the group there can be no other
	 * in-use devices in the group.  The user has done their due diligence
	 * and we should lay no claims to those devices.  In order to do that,
	 * we need to make sure the group is detached from the container.
	 * Without this stall, we're potentially racing with a user process
	 * that may attempt to immediately bind this device to another driver.
	 */
	if (list_empty(&group->device_list))
		wait_event(group->container_q, !group->container);

	vfio_group_put(group);

	return device_data;
}