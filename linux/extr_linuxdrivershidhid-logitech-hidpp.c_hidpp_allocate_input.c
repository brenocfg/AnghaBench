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
struct TYPE_4__ {int /*<<< orphan*/ * parent; } ;
struct TYPE_3__ {int /*<<< orphan*/  version; int /*<<< orphan*/  product; int /*<<< orphan*/  vendor; int /*<<< orphan*/  bustype; } ;
struct input_dev {TYPE_2__ dev; TYPE_1__ id; int /*<<< orphan*/  uniq; int /*<<< orphan*/  phys; int /*<<< orphan*/  name; int /*<<< orphan*/  close; int /*<<< orphan*/  open; } ;
struct hidpp_device {int /*<<< orphan*/  name; } ;
struct hid_device {int /*<<< orphan*/  dev; int /*<<< orphan*/  version; int /*<<< orphan*/  product; int /*<<< orphan*/  vendor; int /*<<< orphan*/  bus; int /*<<< orphan*/  uniq; int /*<<< orphan*/  phys; } ;

/* Variables and functions */
 struct input_dev* devm_input_allocate_device (int /*<<< orphan*/ *) ; 
 struct hidpp_device* hid_get_drvdata (struct hid_device*) ; 
 int /*<<< orphan*/  hidpp_input_close ; 
 int /*<<< orphan*/  hidpp_input_open ; 
 int /*<<< orphan*/  input_set_drvdata (struct input_dev*,struct hid_device*) ; 

__attribute__((used)) static struct input_dev *hidpp_allocate_input(struct hid_device *hdev)
{
	struct input_dev *input_dev = devm_input_allocate_device(&hdev->dev);
	struct hidpp_device *hidpp = hid_get_drvdata(hdev);

	if (!input_dev)
		return NULL;

	input_set_drvdata(input_dev, hdev);
	input_dev->open = hidpp_input_open;
	input_dev->close = hidpp_input_close;

	input_dev->name = hidpp->name;
	input_dev->phys = hdev->phys;
	input_dev->uniq = hdev->uniq;
	input_dev->id.bustype = hdev->bus;
	input_dev->id.vendor  = hdev->vendor;
	input_dev->id.product = hdev->product;
	input_dev->id.version = hdev->version;
	input_dev->dev.parent = &hdev->dev;

	return input_dev;
}