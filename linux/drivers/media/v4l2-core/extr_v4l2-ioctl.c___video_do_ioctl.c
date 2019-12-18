#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct video_device {int dev_debug; int /*<<< orphan*/  prio; int /*<<< orphan*/ * valid_ioctls; TYPE_2__* v4l2_dev; int /*<<< orphan*/  flags; struct v4l2_ioctl_ops* ioctl_ops; } ;
struct v4l2_ioctl_ops {long (* vidioc_default ) (struct file*,void*,int,unsigned int,void*) ;} ;
typedef  struct v4l2_ioctl_info {int flags; unsigned int ioctl; long (* func ) (struct v4l2_ioctl_ops const*,struct file*,void*,void*) ;int /*<<< orphan*/  (* debug ) (void*,int) ;} const v4l2_ioctl_info ;
struct v4l2_fh {int /*<<< orphan*/  prio; scalar_t__ ctrl_handler; } ;
struct mutex {int dummy; } ;
struct file {struct v4l2_fh* private_data; } ;
struct TYPE_4__ {TYPE_1__* mdev; } ;
struct TYPE_3__ {struct mutex req_queue_mutex; } ;

/* Variables and functions */
 long ENODEV ; 
 long ENOTTY ; 
 long ERESTARTSYS ; 
 int INFO_FL_CTRL ; 
 int INFO_FL_PRIO ; 
 int V4L2_DEV_DEBUG_IOCTL ; 
 int V4L2_DEV_DEBUG_IOCTL_ARG ; 
 int V4L2_DEV_DEBUG_STREAMING ; 
 size_t V4L2_FL_USES_V4L2_FH ; 
 unsigned int VIDIOC_DQBUF ; 
 unsigned int VIDIOC_QBUF ; 
 unsigned int VIDIOC_STREAMOFF ; 
 unsigned int VIDIOC_STREAMON ; 
 scalar_t__ _IOC_DIR (unsigned int) ; 
 scalar_t__ _IOC_NONE ; 
 size_t _IOC_NR (unsigned int) ; 
 scalar_t__ _IOC_WRITE ; 
 scalar_t__ mutex_lock_interruptible (struct mutex*) ; 
 int /*<<< orphan*/  mutex_unlock (struct mutex*) ; 
 int /*<<< orphan*/  pr_cont (char*,...) ; 
 int /*<<< orphan*/  pr_warn (char*,int /*<<< orphan*/ ) ; 
 long stub1 (struct v4l2_ioctl_ops const*,struct file*,void*,void*) ; 
 long stub2 (struct file*,void*,int,unsigned int,void*) ; 
 int /*<<< orphan*/  stub3 (void*,int) ; 
 int /*<<< orphan*/  stub4 (void*,int) ; 
 scalar_t__ test_bit (size_t,int /*<<< orphan*/ *) ; 
 scalar_t__ v4l2_device_supports_requests (TYPE_2__*) ; 
 struct mutex* v4l2_ioctl_get_lock (struct video_device*,struct v4l2_fh*,unsigned int,void*) ; 
 struct v4l2_ioctl_info const* v4l2_ioctls ; 
 scalar_t__ v4l2_is_known_ioctl (unsigned int) ; 
 long v4l2_prio_check (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  v4l_print_default (void*,int) ; 
 int /*<<< orphan*/  v4l_printk_ioctl (int /*<<< orphan*/ ,unsigned int) ; 
 struct video_device* video_devdata (struct file*) ; 
 int /*<<< orphan*/  video_device_node_name (struct video_device*) ; 
 int /*<<< orphan*/  video_is_registered (struct video_device*) ; 

__attribute__((used)) static long __video_do_ioctl(struct file *file,
		unsigned int cmd, void *arg)
{
	struct video_device *vfd = video_devdata(file);
	struct mutex *req_queue_lock = NULL;
	struct mutex *lock; /* ioctl serialization mutex */
	const struct v4l2_ioctl_ops *ops = vfd->ioctl_ops;
	bool write_only = false;
	struct v4l2_ioctl_info default_info;
	const struct v4l2_ioctl_info *info;
	void *fh = file->private_data;
	struct v4l2_fh *vfh = NULL;
	int dev_debug = vfd->dev_debug;
	long ret = -ENOTTY;

	if (ops == NULL) {
		pr_warn("%s: has no ioctl_ops.\n",
				video_device_node_name(vfd));
		return ret;
	}

	if (test_bit(V4L2_FL_USES_V4L2_FH, &vfd->flags))
		vfh = file->private_data;

	/*
	 * We need to serialize streamon/off with queueing new requests.
	 * These ioctls may trigger the cancellation of a streaming
	 * operation, and that should not be mixed with queueing a new
	 * request at the same time.
	 */
	if (v4l2_device_supports_requests(vfd->v4l2_dev) &&
	    (cmd == VIDIOC_STREAMON || cmd == VIDIOC_STREAMOFF)) {
		req_queue_lock = &vfd->v4l2_dev->mdev->req_queue_mutex;

		if (mutex_lock_interruptible(req_queue_lock))
			return -ERESTARTSYS;
	}

	lock = v4l2_ioctl_get_lock(vfd, vfh, cmd, arg);

	if (lock && mutex_lock_interruptible(lock)) {
		if (req_queue_lock)
			mutex_unlock(req_queue_lock);
		return -ERESTARTSYS;
	}

	if (!video_is_registered(vfd)) {
		ret = -ENODEV;
		goto unlock;
	}

	if (v4l2_is_known_ioctl(cmd)) {
		info = &v4l2_ioctls[_IOC_NR(cmd)];

		if (!test_bit(_IOC_NR(cmd), vfd->valid_ioctls) &&
		    !((info->flags & INFO_FL_CTRL) && vfh && vfh->ctrl_handler))
			goto done;

		if (vfh && (info->flags & INFO_FL_PRIO)) {
			ret = v4l2_prio_check(vfd->prio, vfh->prio);
			if (ret)
				goto done;
		}
	} else {
		default_info.ioctl = cmd;
		default_info.flags = 0;
		default_info.debug = v4l_print_default;
		info = &default_info;
	}

	write_only = _IOC_DIR(cmd) == _IOC_WRITE;
	if (info != &default_info) {
		ret = info->func(ops, file, fh, arg);
	} else if (!ops->vidioc_default) {
		ret = -ENOTTY;
	} else {
		ret = ops->vidioc_default(file, fh,
			vfh ? v4l2_prio_check(vfd->prio, vfh->prio) >= 0 : 0,
			cmd, arg);
	}

done:
	if (dev_debug & (V4L2_DEV_DEBUG_IOCTL | V4L2_DEV_DEBUG_IOCTL_ARG)) {
		if (!(dev_debug & V4L2_DEV_DEBUG_STREAMING) &&
		    (cmd == VIDIOC_QBUF || cmd == VIDIOC_DQBUF))
			goto unlock;

		v4l_printk_ioctl(video_device_node_name(vfd), cmd);
		if (ret < 0)
			pr_cont(": error %ld", ret);
		if (!(dev_debug & V4L2_DEV_DEBUG_IOCTL_ARG))
			pr_cont("\n");
		else if (_IOC_DIR(cmd) == _IOC_NONE)
			info->debug(arg, write_only);
		else {
			pr_cont(": ");
			info->debug(arg, write_only);
		}
	}

unlock:
	if (lock)
		mutex_unlock(lock);
	if (req_queue_lock)
		mutex_unlock(req_queue_lock);
	return ret;
}