#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  dev_t ;
struct TYPE_6__ {int /*<<< orphan*/  owner; } ;
struct TYPE_5__ {int /*<<< orphan*/  dev; TYPE_2__ cdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEV_NAME ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MAJOR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MINOR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MPORT ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  THIS_MODULE ; 
 int cdev_add (TYPE_2__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  cdev_del (TYPE_2__*) ; 
 int /*<<< orphan*/  cdev_init (TYPE_2__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_class ; 
 int /*<<< orphan*/  device_create (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 TYPE_1__ riocm_cdev ; 
 int /*<<< orphan*/  riocm_cdev_fops ; 
 int /*<<< orphan*/  riocm_debug (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  riocm_error (char*,int) ; 

__attribute__((used)) static int riocm_cdev_add(dev_t devno)
{
	int ret;

	cdev_init(&riocm_cdev.cdev, &riocm_cdev_fops);
	riocm_cdev.cdev.owner = THIS_MODULE;
	ret = cdev_add(&riocm_cdev.cdev, devno, 1);
	if (ret < 0) {
		riocm_error("Cannot register a device with error %d", ret);
		return ret;
	}

	riocm_cdev.dev = device_create(dev_class, NULL, devno, NULL, DEV_NAME);
	if (IS_ERR(riocm_cdev.dev)) {
		cdev_del(&riocm_cdev.cdev);
		return PTR_ERR(riocm_cdev.dev);
	}

	riocm_debug(MPORT, "Added %s cdev(%d:%d)",
		    DEV_NAME, MAJOR(devno), MINOR(devno));

	return 0;
}