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
typedef  int /*<<< orphan*/  dev_t ;

/* Variables and functions */
 scalar_t__ IS_ERR (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  MAJOR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  THIS_MODULE ; 
 int alloc_chrdev_region (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,char*) ; 
 int /*<<< orphan*/ * class_create (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  class_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  major ; 
 int minors ; 
 int /*<<< orphan*/  pr_err (char*,int) ; 
 int /*<<< orphan*/ * usb_gadget_class ; 

__attribute__((used)) static int gprinter_setup(int count)
{
	int status;
	dev_t devt;

	usb_gadget_class = class_create(THIS_MODULE, "usb_printer_gadget");
	if (IS_ERR(usb_gadget_class)) {
		status = PTR_ERR(usb_gadget_class);
		usb_gadget_class = NULL;
		pr_err("unable to create usb_gadget class %d\n", status);
		return status;
	}

	status = alloc_chrdev_region(&devt, 0, count, "USB printer gadget");
	if (status) {
		pr_err("alloc_chrdev_region %d\n", status);
		class_destroy(usb_gadget_class);
		usb_gadget_class = NULL;
		return status;
	}

	major = MAJOR(devt);
	minors = count;

	return status;
}