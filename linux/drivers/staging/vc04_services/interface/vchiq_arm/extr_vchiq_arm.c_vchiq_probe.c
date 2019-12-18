#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct vchiq_drvdata {int /*<<< orphan*/  fw; } ;
struct TYPE_8__ {int /*<<< orphan*/  of_node; } ;
struct platform_device {TYPE_2__ dev; } ;
struct of_device_id {scalar_t__ data; } ;
struct device_node {int dummy; } ;
struct device {int dummy; } ;
struct TYPE_7__ {int /*<<< orphan*/  owner; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOENT ; 
 int EPROBE_DEFER ; 
 scalar_t__ IS_ERR (struct device*) ; 
 int /*<<< orphan*/  MAJOR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MINOR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (struct device*) ; 
 int /*<<< orphan*/  THIS_MODULE ; 
 int /*<<< orphan*/  VCHIQ_VERSION ; 
 int /*<<< orphan*/  VCHIQ_VERSION_MIN ; 
 void* bcm2835_audio ; 
 void* bcm2835_camera ; 
 int cdev_add (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  cdev_del (TYPE_1__*) ; 
 int /*<<< orphan*/  cdev_init (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_err (TYPE_2__*,char*) ; 
 struct device* device_create (int /*<<< orphan*/ ,TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  g_state ; 
 struct device_node* of_find_compatible_node (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*) ; 
 struct of_device_id* of_match_node (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  of_node_put (struct device_node*) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct vchiq_drvdata*) ; 
 int /*<<< orphan*/  rpi_firmware_get (struct device_node*) ; 
 int /*<<< orphan*/  vchiq_arm_log_level ; 
 TYPE_1__ vchiq_cdev ; 
 int /*<<< orphan*/  vchiq_class ; 
 int /*<<< orphan*/  vchiq_debugfs_init () ; 
 int /*<<< orphan*/  vchiq_devid ; 
 int /*<<< orphan*/  vchiq_fops ; 
 int /*<<< orphan*/  vchiq_log_error (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  vchiq_log_info (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vchiq_log_warning (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  vchiq_of_match ; 
 int vchiq_platform_init (struct platform_device*,int /*<<< orphan*/ *) ; 
 void* vchiq_register_child (struct platform_device*,char*) ; 

__attribute__((used)) static int vchiq_probe(struct platform_device *pdev)
{
	struct device_node *fw_node;
	const struct of_device_id *of_id;
	struct vchiq_drvdata *drvdata;
	struct device *vchiq_dev;
	int err;

	of_id = of_match_node(vchiq_of_match, pdev->dev.of_node);
	drvdata = (struct vchiq_drvdata *)of_id->data;
	if (!drvdata)
		return -EINVAL;

	fw_node = of_find_compatible_node(NULL, NULL,
					  "raspberrypi,bcm2835-firmware");
	if (!fw_node) {
		dev_err(&pdev->dev, "Missing firmware node\n");
		return -ENOENT;
	}

	drvdata->fw = rpi_firmware_get(fw_node);
	of_node_put(fw_node);
	if (!drvdata->fw)
		return -EPROBE_DEFER;

	platform_set_drvdata(pdev, drvdata);

	err = vchiq_platform_init(pdev, &g_state);
	if (err)
		goto failed_platform_init;

	cdev_init(&vchiq_cdev, &vchiq_fops);
	vchiq_cdev.owner = THIS_MODULE;
	err = cdev_add(&vchiq_cdev, vchiq_devid, 1);
	if (err) {
		vchiq_log_error(vchiq_arm_log_level,
			"Unable to register device");
		goto failed_platform_init;
	}

	vchiq_dev = device_create(vchiq_class, &pdev->dev, vchiq_devid, NULL,
				  "vchiq");
	if (IS_ERR(vchiq_dev)) {
		err = PTR_ERR(vchiq_dev);
		goto failed_device_create;
	}

	vchiq_debugfs_init();

	vchiq_log_info(vchiq_arm_log_level,
		"vchiq: initialised - version %d (min %d), device %d.%d",
		VCHIQ_VERSION, VCHIQ_VERSION_MIN,
		MAJOR(vchiq_devid), MINOR(vchiq_devid));

	bcm2835_camera = vchiq_register_child(pdev, "bcm2835-camera");
	bcm2835_audio = vchiq_register_child(pdev, "bcm2835_audio");

	return 0;

failed_device_create:
	cdev_del(&vchiq_cdev);
failed_platform_init:
	vchiq_log_warning(vchiq_arm_log_level, "could not load vchiq");
	return err;
}