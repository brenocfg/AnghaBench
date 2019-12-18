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
struct platform_device {int /*<<< orphan*/  dev; int /*<<< orphan*/  name; } ;
struct matrix_keypad_platform_data {int /*<<< orphan*/  wakeup; int /*<<< orphan*/  no_autorepeat; int /*<<< orphan*/  num_col_gpios; int /*<<< orphan*/  num_row_gpios; int /*<<< orphan*/  keymap_data; } ;
struct matrix_keypad {int stopped; struct input_dev* input_dev; int /*<<< orphan*/  lock; int /*<<< orphan*/  work; int /*<<< orphan*/  row_shift; struct matrix_keypad_platform_data const* pdata; } ;
struct TYPE_4__ {int /*<<< orphan*/ * parent; } ;
struct TYPE_3__ {int /*<<< orphan*/  bustype; } ;
struct input_dev {int /*<<< orphan*/  evbit; int /*<<< orphan*/  close; int /*<<< orphan*/  open; TYPE_2__ dev; TYPE_1__ id; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUS_HOST ; 
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  EV_MSC ; 
 int /*<<< orphan*/  EV_REP ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_DELAYED_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ IS_ERR (struct matrix_keypad_platform_data const*) ; 
 int /*<<< orphan*/  MSC_SCAN ; 
 int PTR_ERR (struct matrix_keypad_platform_data const*) ; 
 int /*<<< orphan*/  __set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 struct matrix_keypad_platform_data* dev_get_platdata (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  device_init_wakeup (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_count_order (int /*<<< orphan*/ ) ; 
 struct input_dev* input_allocate_device () ; 
 int /*<<< orphan*/  input_free_device (struct input_dev*) ; 
 int input_register_device (struct input_dev*) ; 
 int /*<<< orphan*/  input_set_capability (struct input_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  input_set_drvdata (struct input_dev*,struct matrix_keypad*) ; 
 int /*<<< orphan*/  kfree (struct matrix_keypad*) ; 
 struct matrix_keypad* kzalloc (int,int /*<<< orphan*/ ) ; 
 int matrix_keypad_build_keymap (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct input_dev*) ; 
 int /*<<< orphan*/  matrix_keypad_free_gpio (struct matrix_keypad*) ; 
 int matrix_keypad_init_gpio (struct platform_device*,struct matrix_keypad*) ; 
 struct matrix_keypad_platform_data* matrix_keypad_parse_dt (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  matrix_keypad_scan ; 
 int /*<<< orphan*/  matrix_keypad_start ; 
 int /*<<< orphan*/  matrix_keypad_stop ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct matrix_keypad*) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int matrix_keypad_probe(struct platform_device *pdev)
{
	const struct matrix_keypad_platform_data *pdata;
	struct matrix_keypad *keypad;
	struct input_dev *input_dev;
	int err;

	pdata = dev_get_platdata(&pdev->dev);
	if (!pdata) {
		pdata = matrix_keypad_parse_dt(&pdev->dev);
		if (IS_ERR(pdata))
			return PTR_ERR(pdata);
	} else if (!pdata->keymap_data) {
		dev_err(&pdev->dev, "no keymap data defined\n");
		return -EINVAL;
	}

	keypad = kzalloc(sizeof(struct matrix_keypad), GFP_KERNEL);
	input_dev = input_allocate_device();
	if (!keypad || !input_dev) {
		err = -ENOMEM;
		goto err_free_mem;
	}

	keypad->input_dev = input_dev;
	keypad->pdata = pdata;
	keypad->row_shift = get_count_order(pdata->num_col_gpios);
	keypad->stopped = true;
	INIT_DELAYED_WORK(&keypad->work, matrix_keypad_scan);
	spin_lock_init(&keypad->lock);

	input_dev->name		= pdev->name;
	input_dev->id.bustype	= BUS_HOST;
	input_dev->dev.parent	= &pdev->dev;
	input_dev->open		= matrix_keypad_start;
	input_dev->close	= matrix_keypad_stop;

	err = matrix_keypad_build_keymap(pdata->keymap_data, NULL,
					 pdata->num_row_gpios,
					 pdata->num_col_gpios,
					 NULL, input_dev);
	if (err) {
		dev_err(&pdev->dev, "failed to build keymap\n");
		goto err_free_mem;
	}

	if (!pdata->no_autorepeat)
		__set_bit(EV_REP, input_dev->evbit);
	input_set_capability(input_dev, EV_MSC, MSC_SCAN);
	input_set_drvdata(input_dev, keypad);

	err = matrix_keypad_init_gpio(pdev, keypad);
	if (err)
		goto err_free_mem;

	err = input_register_device(keypad->input_dev);
	if (err)
		goto err_free_gpio;

	device_init_wakeup(&pdev->dev, pdata->wakeup);
	platform_set_drvdata(pdev, keypad);

	return 0;

err_free_gpio:
	matrix_keypad_free_gpio(keypad);
err_free_mem:
	input_free_device(input_dev);
	kfree(keypad);
	return err;
}