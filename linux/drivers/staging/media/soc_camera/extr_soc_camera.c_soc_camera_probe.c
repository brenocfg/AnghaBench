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
struct soc_camera_host_desc {int (* add_device ) (struct soc_camera_device*) ;int /*<<< orphan*/  (* del_device ) (struct soc_camera_device*) ;scalar_t__ board_info; scalar_t__ module_name; } ;
struct soc_camera_host {int /*<<< orphan*/  host_lock; } ;
struct soc_camera_device {int /*<<< orphan*/  ctrl_handler; int /*<<< orphan*/ * vdev; int /*<<< orphan*/  pdev; } ;
struct soc_camera_desc {struct soc_camera_host_desc host_desc; } ;
struct device {TYPE_1__* driver; } ;
struct TYPE_2__ {int /*<<< orphan*/  owner; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENODEV ; 
 int EPROBE_DEFER ; 
 int /*<<< orphan*/  dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_name (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  module_put (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int request_module (scalar_t__) ; 
 int soc_camera_clock_start (struct soc_camera_host*) ; 
 int /*<<< orphan*/  soc_camera_clock_stop (struct soc_camera_host*) ; 
 int /*<<< orphan*/  soc_camera_i2c_free (struct soc_camera_device*) ; 
 int soc_camera_i2c_init (struct soc_camera_device*,struct soc_camera_desc*) ; 
 int soc_camera_probe_finish (struct soc_camera_device*) ; 
 int stub1 (struct soc_camera_device*) ; 
 int /*<<< orphan*/  stub2 (struct soc_camera_device*) ; 
 int /*<<< orphan*/  stub3 (struct soc_camera_device*) ; 
 struct device* to_soc_camera_control (struct soc_camera_device*) ; 
 struct soc_camera_desc* to_soc_camera_desc (struct soc_camera_device*) ; 
 int /*<<< orphan*/  try_module_get (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  v4l2_ctrl_handler_free (int /*<<< orphan*/ *) ; 
 int v4l2_ctrl_handler_init (int /*<<< orphan*/ *,int) ; 
 int video_dev_create (struct soc_camera_device*) ; 
 int /*<<< orphan*/  video_device_release (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int soc_camera_probe(struct soc_camera_host *ici,
			    struct soc_camera_device *icd)
{
	struct soc_camera_desc *sdesc = to_soc_camera_desc(icd);
	struct soc_camera_host_desc *shd = &sdesc->host_desc;
	struct device *control = NULL;
	int ret;

	dev_info(icd->pdev, "Probing %s\n", dev_name(icd->pdev));

	/*
	 * Currently the subdev with the largest number of controls (13) is
	 * ov6550. So let's pick 16 as a hint for the control handler. Note
	 * that this is a hint only: too large and you waste some memory, too
	 * small and there is a (very) small performance hit when looking up
	 * controls in the internal hash.
	 */
	ret = v4l2_ctrl_handler_init(&icd->ctrl_handler, 16);
	if (ret < 0)
		return ret;

	/* Must have icd->vdev before registering the device */
	ret = video_dev_create(icd);
	if (ret < 0)
		goto evdc;

	/*
	 * ..._video_start() will create a device node, video_register_device()
	 * itself is protected against concurrent open() calls, but we also have
	 * to protect our data also during client probing.
	 */

	/* Non-i2c cameras, e.g., soc_camera_platform, have no board_info */
	if (shd->board_info) {
		ret = soc_camera_i2c_init(icd, sdesc);
		if (ret < 0 && ret != -EPROBE_DEFER)
			goto eadd;
	} else if (!shd->add_device || !shd->del_device) {
		ret = -EINVAL;
		goto eadd;
	} else {
		ret = soc_camera_clock_start(ici);
		if (ret < 0)
			goto eadd;

		if (shd->module_name)
			ret = request_module(shd->module_name);

		ret = shd->add_device(icd);
		if (ret < 0)
			goto eadddev;

		/*
		 * FIXME: this is racy, have to use driver-binding notification,
		 * when it is available
		 */
		control = to_soc_camera_control(icd);
		if (!control || !control->driver || !dev_get_drvdata(control) ||
		    !try_module_get(control->driver->owner)) {
			shd->del_device(icd);
			ret = -ENODEV;
			goto enodrv;
		}
	}

	mutex_lock(&ici->host_lock);
	ret = soc_camera_probe_finish(icd);
	mutex_unlock(&ici->host_lock);
	if (ret < 0)
		goto efinish;

	return 0;

efinish:
	if (shd->board_info) {
		soc_camera_i2c_free(icd);
	} else {
		shd->del_device(icd);
		module_put(control->driver->owner);
enodrv:
eadddev:
		soc_camera_clock_stop(ici);
	}
eadd:
	if (icd->vdev) {
		video_device_release(icd->vdev);
		icd->vdev = NULL;
	}
evdc:
	v4l2_ctrl_handler_free(&icd->ctrl_handler);
	return ret;
}