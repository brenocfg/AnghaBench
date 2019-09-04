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
struct device {int dummy; } ;
struct ace_device {int id; int irq; int bus_width; scalar_t__ physaddr; struct device* dev; } ;
typedef  scalar_t__ resource_size_t ;

/* Variables and functions */
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int ace_setup (struct ace_device*) ; 
 int /*<<< orphan*/  dev_dbg (struct device*,char*,struct device*) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,int) ; 
 int /*<<< orphan*/  dev_set_drvdata (struct device*,struct ace_device*) ; 
 int /*<<< orphan*/  kfree (struct ace_device*) ; 
 struct ace_device* kzalloc (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ace_alloc(struct device *dev, int id, resource_size_t physaddr,
		     int irq, int bus_width)
{
	struct ace_device *ace;
	int rc;
	dev_dbg(dev, "ace_alloc(%p)\n", dev);

	if (!physaddr) {
		rc = -ENODEV;
		goto err_noreg;
	}

	/* Allocate and initialize the ace device structure */
	ace = kzalloc(sizeof(struct ace_device), GFP_KERNEL);
	if (!ace) {
		rc = -ENOMEM;
		goto err_alloc;
	}

	ace->dev = dev;
	ace->id = id;
	ace->physaddr = physaddr;
	ace->irq = irq;
	ace->bus_width = bus_width;

	/* Call the setup code */
	rc = ace_setup(ace);
	if (rc)
		goto err_setup;

	dev_set_drvdata(dev, ace);
	return 0;

err_setup:
	dev_set_drvdata(dev, NULL);
	kfree(ace);
err_alloc:
err_noreg:
	dev_err(dev, "could not initialize device, err=%i\n", rc);
	return rc;
}