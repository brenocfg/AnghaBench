#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  name; int /*<<< orphan*/  release; } ;
struct most_video_dev {int ch_idx; TYPE_1__ v4l2_dev; int /*<<< orphan*/  list; struct most_interface* iface; int /*<<< orphan*/  pending_mbos; int /*<<< orphan*/  list_lock; int /*<<< orphan*/  access_ref; int /*<<< orphan*/  lock; } ;
struct most_interface {int dummy; } ;
struct most_channel_config {scalar_t__ direction; scalar_t__ data_type; } ;

/* Variables and functions */
 int EEXIST ; 
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 scalar_t__ MOST_CH_ISOC ; 
 scalar_t__ MOST_CH_RX ; 
 scalar_t__ MOST_CH_SYNC ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int) ; 
 int comp_register_videodev (struct most_video_dev*) ; 
 int /*<<< orphan*/  comp_v4l2_dev_release ; 
 struct most_video_dev* get_comp_dev (struct most_interface*,int) ; 
 int /*<<< orphan*/  kfree (struct most_video_dev*) ; 
 struct most_video_dev* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_lock ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strlcpy (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  v4l2_device_disconnect (TYPE_1__*) ; 
 int /*<<< orphan*/  v4l2_device_put (TYPE_1__*) ; 
 int v4l2_device_register (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  video_devices ; 

__attribute__((used)) static int comp_probe_channel(struct most_interface *iface, int channel_idx,
			      struct most_channel_config *ccfg, char *name,
			      char *args)
{
	int ret;
	struct most_video_dev *mdev = get_comp_dev(iface, channel_idx);

	if (mdev) {
		pr_err("channel already linked\n");
		return -EEXIST;
	}

	if (ccfg->direction != MOST_CH_RX) {
		pr_err("wrong direction, expect rx\n");
		return -EINVAL;
	}

	if (ccfg->data_type != MOST_CH_SYNC &&
	    ccfg->data_type != MOST_CH_ISOC) {
		pr_err("wrong channel type, expect sync or isoc\n");
		return -EINVAL;
	}

	mdev = kzalloc(sizeof(*mdev), GFP_KERNEL);
	if (!mdev)
		return -ENOMEM;

	mutex_init(&mdev->lock);
	atomic_set(&mdev->access_ref, -1);
	spin_lock_init(&mdev->list_lock);
	INIT_LIST_HEAD(&mdev->pending_mbos);
	mdev->iface = iface;
	mdev->ch_idx = channel_idx;
	mdev->v4l2_dev.release = comp_v4l2_dev_release;

	/* Create the v4l2_device */
	strlcpy(mdev->v4l2_dev.name, name, sizeof(mdev->v4l2_dev.name));
	ret = v4l2_device_register(NULL, &mdev->v4l2_dev);
	if (ret) {
		pr_err("v4l2_device_register() failed\n");
		kfree(mdev);
		return ret;
	}

	ret = comp_register_videodev(mdev);
	if (ret)
		goto err_unreg;

	spin_lock_irq(&list_lock);
	list_add(&mdev->list, &video_devices);
	spin_unlock_irq(&list_lock);
	return 0;

err_unreg:
	v4l2_device_disconnect(&mdev->v4l2_dev);
	v4l2_device_put(&mdev->v4l2_dev);
	return ret;
}