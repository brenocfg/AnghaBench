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
typedef  int u8 ;
struct lm8323_platform_data {int size_x; int size_y; scalar_t__ repeat; int /*<<< orphan*/ * keymap; scalar_t__ name; int /*<<< orphan*/ * pwm_names; int /*<<< orphan*/  active_time; int /*<<< orphan*/  debounce_time; } ;
struct lm8323_chip {int size_x; int size_y; int kp_enabled; TYPE_1__* pwm; int /*<<< orphan*/ * keymap; int /*<<< orphan*/  phys; int /*<<< orphan*/  active_time; int /*<<< orphan*/  debounce_time; int /*<<< orphan*/  lock; struct input_dev* idev; struct i2c_client* client; } ;
struct input_dev {char* name; int* evbit; int* mscbit; int* keybit; int /*<<< orphan*/  phys; } ;
struct i2c_device_id {int dummy; } ;
struct i2c_client {int irq; int /*<<< orphan*/  dev; } ;
struct TYPE_2__ {int /*<<< orphan*/  cdev; scalar_t__ enabled; } ;

/* Variables and functions */
 int BIT (int /*<<< orphan*/ ) ; 
 int EINVAL ; 
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  EV_KEY ; 
 int /*<<< orphan*/  EV_MSC ; 
 int /*<<< orphan*/  EV_REP ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int INT_NOINIT ; 
 int IRQF_ONESHOT ; 
 int IRQF_TRIGGER_LOW ; 
 int /*<<< orphan*/  KEY_RESERVED ; 
 int /*<<< orphan*/  LM8323_CMD_READ_INT ; 
 int LM8323_KEYMAP_SIZE ; 
 int LM8323_NUM_PWMS ; 
 int /*<<< orphan*/  MSC_SCAN ; 
 int /*<<< orphan*/  __clear_bit (int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  __set_bit (int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  dev_attr_disable_kp ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,...) ; 
 struct lm8323_platform_data* dev_get_platdata (int /*<<< orphan*/ *) ; 
 char* dev_name (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_vdbg (int /*<<< orphan*/ *,char*,int,int) ; 
 int device_create_file (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  device_init_wakeup (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  device_remove_file (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  enable_irq_wake (int) ; 
 int /*<<< orphan*/  i2c_set_clientdata (struct i2c_client*,struct lm8323_chip*) ; 
 int init_pwm (struct lm8323_chip*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct input_dev* input_allocate_device () ; 
 int /*<<< orphan*/  input_free_device (struct input_dev*) ; 
 int input_register_device (struct input_dev*) ; 
 int /*<<< orphan*/  input_unregister_device (struct input_dev*) ; 
 unsigned long jiffies ; 
 int /*<<< orphan*/  kfree (struct lm8323_chip*) ; 
 struct lm8323_chip* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  led_classdev_unregister (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lm8323_configure (struct lm8323_chip*) ; 
 int /*<<< orphan*/  lm8323_irq ; 
 int lm8323_read (struct lm8323_chip*,int /*<<< orphan*/ ,int*,int) ; 
 scalar_t__ lm8323_read_id (struct lm8323_chip*,int*) ; 
 int /*<<< orphan*/  lm8323_reset (struct lm8323_chip*) ; 
 unsigned long msecs_to_jiffies (int) ; 
 int /*<<< orphan*/  msleep (int) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int request_threaded_irq (int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,char*,struct lm8323_chip*) ; 
 int /*<<< orphan*/  snprintf (int /*<<< orphan*/ ,int,char*,char*) ; 
 scalar_t__ time_after (unsigned long,unsigned long) ; 

__attribute__((used)) static int lm8323_probe(struct i2c_client *client,
				  const struct i2c_device_id *id)
{
	struct lm8323_platform_data *pdata = dev_get_platdata(&client->dev);
	struct input_dev *idev;
	struct lm8323_chip *lm;
	int pwm;
	int i, err;
	unsigned long tmo;
	u8 data[2];

	if (!pdata || !pdata->size_x || !pdata->size_y) {
		dev_err(&client->dev, "missing platform_data\n");
		return -EINVAL;
	}

	if (pdata->size_x > 8) {
		dev_err(&client->dev, "invalid x size %d specified\n",
			pdata->size_x);
		return -EINVAL;
	}

	if (pdata->size_y > 12) {
		dev_err(&client->dev, "invalid y size %d specified\n",
			pdata->size_y);
		return -EINVAL;
	}

	lm = kzalloc(sizeof *lm, GFP_KERNEL);
	idev = input_allocate_device();
	if (!lm || !idev) {
		err = -ENOMEM;
		goto fail1;
	}

	lm->client = client;
	lm->idev = idev;
	mutex_init(&lm->lock);

	lm->size_x = pdata->size_x;
	lm->size_y = pdata->size_y;
	dev_vdbg(&client->dev, "Keypad size: %d x %d\n",
		 lm->size_x, lm->size_y);

	lm->debounce_time = pdata->debounce_time;
	lm->active_time = pdata->active_time;

	lm8323_reset(lm);

	/* Nothing's set up to service the IRQ yet, so just spin for max.
	 * 100ms until we can configure. */
	tmo = jiffies + msecs_to_jiffies(100);
	while (lm8323_read(lm, LM8323_CMD_READ_INT, data, 1) == 1) {
		if (data[0] & INT_NOINIT)
			break;

		if (time_after(jiffies, tmo)) {
			dev_err(&client->dev,
				"timeout waiting for initialisation\n");
			break;
		}

		msleep(1);
	}

	lm8323_configure(lm);

	/* If a true probe check the device */
	if (lm8323_read_id(lm, data) != 0) {
		dev_err(&client->dev, "device not found\n");
		err = -ENODEV;
		goto fail1;
	}

	for (pwm = 0; pwm < LM8323_NUM_PWMS; pwm++) {
		err = init_pwm(lm, pwm + 1, &client->dev,
			       pdata->pwm_names[pwm]);
		if (err < 0)
			goto fail2;
	}

	lm->kp_enabled = true;
	err = device_create_file(&client->dev, &dev_attr_disable_kp);
	if (err < 0)
		goto fail2;

	idev->name = pdata->name ? : "LM8323 keypad";
	snprintf(lm->phys, sizeof(lm->phys),
		 "%s/input-kp", dev_name(&client->dev));
	idev->phys = lm->phys;

	idev->evbit[0] = BIT(EV_KEY) | BIT(EV_MSC);
	__set_bit(MSC_SCAN, idev->mscbit);
	for (i = 0; i < LM8323_KEYMAP_SIZE; i++) {
		__set_bit(pdata->keymap[i], idev->keybit);
		lm->keymap[i] = pdata->keymap[i];
	}
	__clear_bit(KEY_RESERVED, idev->keybit);

	if (pdata->repeat)
		__set_bit(EV_REP, idev->evbit);

	err = input_register_device(idev);
	if (err) {
		dev_dbg(&client->dev, "error registering input device\n");
		goto fail3;
	}

	err = request_threaded_irq(client->irq, NULL, lm8323_irq,
			  IRQF_TRIGGER_LOW|IRQF_ONESHOT, "lm8323", lm);
	if (err) {
		dev_err(&client->dev, "could not get IRQ %d\n", client->irq);
		goto fail4;
	}

	i2c_set_clientdata(client, lm);

	device_init_wakeup(&client->dev, 1);
	enable_irq_wake(client->irq);

	return 0;

fail4:
	input_unregister_device(idev);
	idev = NULL;
fail3:
	device_remove_file(&client->dev, &dev_attr_disable_kp);
fail2:
	while (--pwm >= 0)
		if (lm->pwm[pwm].enabled)
			led_classdev_unregister(&lm->pwm[pwm].cdev);
fail1:
	input_free_device(idev);
	kfree(lm);
	return err;
}