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
struct serdev_device {int /*<<< orphan*/  dev; } ;
struct gnss_serial {struct gnss_device* gdev; struct serdev_device* serdev; } ;
struct gnss_device {int /*<<< orphan*/ * ops; } ;

/* Variables and functions */
 int ENOMEM ; 
 struct gnss_serial* ERR_PTR (int) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 struct gnss_device* gnss_allocate_device (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gnss_put_device (struct gnss_device*) ; 
 int /*<<< orphan*/  gnss_serial_gnss_ops ; 
 int gnss_serial_parse_dt (struct serdev_device*) ; 
 int /*<<< orphan*/  gnss_serial_serdev_ops ; 
 int /*<<< orphan*/  gnss_set_drvdata (struct gnss_device*,struct gnss_serial*) ; 
 int /*<<< orphan*/  kfree (struct gnss_serial*) ; 
 struct gnss_serial* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  serdev_device_set_client_ops (struct serdev_device*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  serdev_device_set_drvdata (struct serdev_device*,struct gnss_serial*) ; 

struct gnss_serial *gnss_serial_allocate(struct serdev_device *serdev,
						size_t data_size)
{
	struct gnss_serial *gserial;
	struct gnss_device *gdev;
	int ret;

	gserial = kzalloc(sizeof(*gserial) + data_size, GFP_KERNEL);
	if (!gserial)
		return ERR_PTR(-ENOMEM);

	gdev = gnss_allocate_device(&serdev->dev);
	if (!gdev) {
		ret = -ENOMEM;
		goto err_free_gserial;
	}

	gdev->ops = &gnss_serial_gnss_ops;
	gnss_set_drvdata(gdev, gserial);

	gserial->serdev = serdev;
	gserial->gdev = gdev;

	serdev_device_set_drvdata(serdev, gserial);
	serdev_device_set_client_ops(serdev, &gnss_serial_serdev_ops);

	ret = gnss_serial_parse_dt(serdev);
	if (ret)
		goto err_put_device;

	return gserial;

err_put_device:
	gnss_put_device(gserial->gdev);
err_free_gserial:
	kfree(gserial);

	return ERR_PTR(ret);
}