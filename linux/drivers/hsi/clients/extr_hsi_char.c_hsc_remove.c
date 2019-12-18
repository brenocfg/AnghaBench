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
struct hsi_client {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;
struct hsc_client_data {TYPE_1__ cdev; } ;
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  dev_t ;

/* Variables and functions */
 int /*<<< orphan*/  HSC_DEVS ; 
 int /*<<< orphan*/  cdev_del (TYPE_1__*) ; 
 struct hsc_client_data* hsi_client_drvdata (struct hsi_client*) ; 
 int /*<<< orphan*/  hsi_client_set_drvdata (struct hsi_client*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct hsc_client_data*) ; 
 struct hsi_client* to_hsi_client (struct device*) ; 
 int /*<<< orphan*/  unregister_chrdev_region (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int hsc_remove(struct device *dev)
{
	struct hsi_client *cl = to_hsi_client(dev);
	struct hsc_client_data *cl_data = hsi_client_drvdata(cl);
	dev_t hsc_dev = cl_data->cdev.dev;

	cdev_del(&cl_data->cdev);
	unregister_chrdev_region(hsc_dev, HSC_DEVS);
	hsi_client_set_drvdata(cl, NULL);
	kfree(cl_data);

	return 0;
}