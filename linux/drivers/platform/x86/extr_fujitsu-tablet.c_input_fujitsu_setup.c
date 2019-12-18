#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int vendor; int product; int version; int /*<<< orphan*/  bustype; } ;
struct TYPE_5__ {struct device* parent; } ;
struct input_dev {char const* phys; char const* name; int keycodesize; int keycodemax; int /*<<< orphan*/  evbit; scalar_t__* keycode; TYPE_2__ id; TYPE_1__ dev; } ;
struct device {int dummy; } ;
struct TYPE_7__ {scalar_t__* keymap; } ;
struct TYPE_8__ {struct input_dev* idev; TYPE_3__ config; } ;

/* Variables and functions */
 int ARRAY_SIZE (scalar_t__*) ; 
 int /*<<< orphan*/  BUS_HOST ; 
 int ENOMEM ; 
 int /*<<< orphan*/  EV_KEY ; 
 int /*<<< orphan*/  EV_MSC ; 
 int /*<<< orphan*/  EV_REP ; 
 int /*<<< orphan*/  EV_SW ; 
 scalar_t__ MSC_SCAN ; 
 scalar_t__ SW_DOCK ; 
 scalar_t__ SW_TABLET_MODE ; 
 int /*<<< orphan*/  __set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_4__ fujitsu ; 
 struct input_dev* input_allocate_device () ; 
 int /*<<< orphan*/  input_free_device (struct input_dev*) ; 
 int input_register_device (struct input_dev*) ; 
 int /*<<< orphan*/  input_set_capability (struct input_dev*,int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static int input_fujitsu_setup(struct device *parent, const char *name,
			       const char *phys)
{
	struct input_dev *idev;
	int error;
	int i;

	idev = input_allocate_device();
	if (!idev)
		return -ENOMEM;

	idev->dev.parent = parent;
	idev->phys = phys;
	idev->name = name;
	idev->id.bustype = BUS_HOST;
	idev->id.vendor  = 0x1734;	/* Fujitsu Siemens Computer GmbH */
	idev->id.product = 0x0001;
	idev->id.version = 0x0101;

	idev->keycode = fujitsu.config.keymap;
	idev->keycodesize = sizeof(fujitsu.config.keymap[0]);
	idev->keycodemax = ARRAY_SIZE(fujitsu.config.keymap);

	__set_bit(EV_REP, idev->evbit);

	for (i = 0; i < ARRAY_SIZE(fujitsu.config.keymap); i++)
		if (fujitsu.config.keymap[i])
			input_set_capability(idev, EV_KEY, fujitsu.config.keymap[i]);

	input_set_capability(idev, EV_MSC, MSC_SCAN);

	input_set_capability(idev, EV_SW, SW_DOCK);
	input_set_capability(idev, EV_SW, SW_TABLET_MODE);

	error = input_register_device(idev);
	if (error) {
		input_free_device(idev);
		return error;
	}

	fujitsu.idev = idev;
	return 0;
}