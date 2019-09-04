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
typedef  int /*<<< orphan*/  u8 ;
struct mei_device {scalar_t__ dev_state; scalar_t__ tx_queue_limit; int /*<<< orphan*/  device_lock; } ;
struct TYPE_2__ {int /*<<< orphan*/  data; } ;
struct mei_cl_cb {int internal; int blocking; TYPE_1__ buf; } ;
struct mei_cl {scalar_t__ tx_cb_queued; scalar_t__ writing_state; int /*<<< orphan*/  tx_wait; int /*<<< orphan*/  me_cl; struct mei_device* dev; } ;
typedef  int ssize_t ;

/* Variables and functions */
 int EFBIG ; 
 int EINTR ; 
 int ENODEV ; 
 int ENOMEM ; 
 int ENOTTY ; 
 unsigned int MEI_CL_IO_TX_BLOCKING ; 
 unsigned int MEI_CL_IO_TX_INTERNAL ; 
 scalar_t__ MEI_DEV_ENABLED ; 
 int /*<<< orphan*/  MEI_FOP_WRITE ; 
 scalar_t__ MEI_WRITE_COMPLETE ; 
 scalar_t__ WARN_ON (int) ; 
 int /*<<< orphan*/  current ; 
 struct mei_cl_cb* mei_cl_alloc_cb (struct mei_cl*,size_t,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mei_cl_is_connected (struct mei_cl*) ; 
 size_t mei_cl_mtu (struct mei_cl*) ; 
 int mei_cl_write (struct mei_cl*,struct mei_cl_cb*) ; 
 int /*<<< orphan*/  mei_me_cl_is_active (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ signal_pending (int /*<<< orphan*/ ) ; 
 int wait_event_interruptible (int /*<<< orphan*/ ,int) ; 

ssize_t __mei_cl_send(struct mei_cl *cl, u8 *buf, size_t length,
		      unsigned int mode)
{
	struct mei_device *bus;
	struct mei_cl_cb *cb;
	ssize_t rets;

	if (WARN_ON(!cl || !cl->dev))
		return -ENODEV;

	bus = cl->dev;

	mutex_lock(&bus->device_lock);
	if (bus->dev_state != MEI_DEV_ENABLED) {
		rets = -ENODEV;
		goto out;
	}

	if (!mei_cl_is_connected(cl)) {
		rets = -ENODEV;
		goto out;
	}

	/* Check if we have an ME client device */
	if (!mei_me_cl_is_active(cl->me_cl)) {
		rets = -ENOTTY;
		goto out;
	}

	if (length > mei_cl_mtu(cl)) {
		rets = -EFBIG;
		goto out;
	}

	while (cl->tx_cb_queued >= bus->tx_queue_limit) {
		mutex_unlock(&bus->device_lock);
		rets = wait_event_interruptible(cl->tx_wait,
				cl->writing_state == MEI_WRITE_COMPLETE ||
				(!mei_cl_is_connected(cl)));
		mutex_lock(&bus->device_lock);
		if (rets) {
			if (signal_pending(current))
				rets = -EINTR;
			goto out;
		}
		if (!mei_cl_is_connected(cl)) {
			rets = -ENODEV;
			goto out;
		}
	}

	cb = mei_cl_alloc_cb(cl, length, MEI_FOP_WRITE, NULL);
	if (!cb) {
		rets = -ENOMEM;
		goto out;
	}

	cb->internal = !!(mode & MEI_CL_IO_TX_INTERNAL);
	cb->blocking = !!(mode & MEI_CL_IO_TX_BLOCKING);
	memcpy(cb->buf.data, buf, length);

	rets = mei_cl_write(cl, cb);

out:
	mutex_unlock(&bus->device_lock);

	return rets;
}