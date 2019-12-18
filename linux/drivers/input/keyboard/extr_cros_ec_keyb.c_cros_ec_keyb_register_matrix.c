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
struct TYPE_4__ {struct device* parent; } ;
struct TYPE_3__ {int version; scalar_t__ product; int /*<<< orphan*/  bustype; } ;
struct input_dev {char const* phys; TYPE_2__ dev; TYPE_1__ id; int /*<<< orphan*/  evbit; int /*<<< orphan*/  name; } ;
struct device {int /*<<< orphan*/  of_node; } ;
struct cros_ec_keyb {struct input_dev* idev; int /*<<< orphan*/  cols; int /*<<< orphan*/  row_shift; int /*<<< orphan*/  rows; int /*<<< orphan*/  ghost_filter; void* old_kb_state; void* valid_keys; struct device* dev; struct cros_ec_device* ec; } ;
struct cros_ec_device {int /*<<< orphan*/  phys_name; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUS_VIRTUAL ; 
 int /*<<< orphan*/  CROS_EC_DEV_NAME ; 
 int ENOMEM ; 
 int /*<<< orphan*/  EV_MSC ; 
 int /*<<< orphan*/  EV_REP ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  MSC_SCAN ; 
 int /*<<< orphan*/  __set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cros_ec_keyb_compute_valid_keys (struct cros_ec_keyb*) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 struct input_dev* devm_input_allocate_device (struct device*) ; 
 char* devm_kasprintf (struct device*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 void* devm_kzalloc (struct device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_count_order (int /*<<< orphan*/ ) ; 
 int input_register_device (struct input_dev*) ; 
 int /*<<< orphan*/  input_set_capability (struct input_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  input_set_drvdata (struct input_dev*,struct cros_ec_keyb*) ; 
 int matrix_keypad_build_keymap (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct input_dev*) ; 
 int matrix_keypad_parse_properties (struct device*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  of_property_read_bool (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int cros_ec_keyb_register_matrix(struct cros_ec_keyb *ckdev)
{
	struct cros_ec_device *ec_dev = ckdev->ec;
	struct device *dev = ckdev->dev;
	struct input_dev *idev;
	const char *phys;
	int err;

	err = matrix_keypad_parse_properties(dev, &ckdev->rows, &ckdev->cols);
	if (err)
		return err;

	ckdev->valid_keys = devm_kzalloc(dev, ckdev->cols, GFP_KERNEL);
	if (!ckdev->valid_keys)
		return -ENOMEM;

	ckdev->old_kb_state = devm_kzalloc(dev, ckdev->cols, GFP_KERNEL);
	if (!ckdev->old_kb_state)
		return -ENOMEM;

	/*
	 * We call the keyboard matrix 'input0'. Allocate phys before input
	 * dev, to ensure correct tear-down ordering.
	 */
	phys = devm_kasprintf(dev, GFP_KERNEL, "%s/input0", ec_dev->phys_name);
	if (!phys)
		return -ENOMEM;

	idev = devm_input_allocate_device(dev);
	if (!idev)
		return -ENOMEM;

	idev->name = CROS_EC_DEV_NAME;
	idev->phys = phys;
	__set_bit(EV_REP, idev->evbit);

	idev->id.bustype = BUS_VIRTUAL;
	idev->id.version = 1;
	idev->id.product = 0;
	idev->dev.parent = dev;

	ckdev->ghost_filter = of_property_read_bool(dev->of_node,
					"google,needs-ghost-filter");

	err = matrix_keypad_build_keymap(NULL, NULL, ckdev->rows, ckdev->cols,
					 NULL, idev);
	if (err) {
		dev_err(dev, "cannot build key matrix\n");
		return err;
	}

	ckdev->row_shift = get_count_order(ckdev->cols);

	input_set_capability(idev, EV_MSC, MSC_SCAN);
	input_set_drvdata(idev, ckdev);
	ckdev->idev = idev;
	cros_ec_keyb_compute_valid_keys(ckdev);

	err = input_register_device(ckdev->idev);
	if (err) {
		dev_err(dev, "cannot register input device\n");
		return err;
	}

	return 0;
}