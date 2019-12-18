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
struct TYPE_3__ {int /*<<< orphan*/  type; } ;
struct serio {int /*<<< orphan*/  phys; int /*<<< orphan*/  name; TYPE_2__ dev; struct ps2_gpio_data* port_data; int /*<<< orphan*/ * write; int /*<<< orphan*/  close; int /*<<< orphan*/  open; TYPE_1__ id; } ;
struct ps2_gpio_data {int irq; int tx_cnt; int /*<<< orphan*/  tx_mutex; int /*<<< orphan*/  tx_done; int /*<<< orphan*/  tx_work; int /*<<< orphan*/  mode; struct device* dev; struct serio* serio; scalar_t__ write_enable; int /*<<< orphan*/  gpio_clk; int /*<<< orphan*/  gpio_data; } ;
struct device {int dummy; } ;
struct platform_device {struct device dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRIVER_NAME ; 
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_DELAYED_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IRQF_NO_THREAD ; 
 int /*<<< orphan*/  PS2_MODE_RX ; 
 int /*<<< orphan*/  SERIO_8042 ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,...) ; 
 int /*<<< orphan*/  dev_name (struct device*) ; 
 struct ps2_gpio_data* devm_kzalloc (struct device*,int,int /*<<< orphan*/ ) ; 
 int devm_request_irq (struct device*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct ps2_gpio_data*) ; 
 int /*<<< orphan*/  disable_irq (int) ; 
 scalar_t__ gpiod_cansleep (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  init_completion (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct serio*) ; 
 struct serio* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int platform_get_irq (struct platform_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct ps2_gpio_data*) ; 
 int /*<<< orphan*/  ps2_gpio_close ; 
 int ps2_gpio_get_props (struct device*,struct ps2_gpio_data*) ; 
 int /*<<< orphan*/  ps2_gpio_irq ; 
 int /*<<< orphan*/  ps2_gpio_open ; 
 int /*<<< orphan*/  ps2_gpio_tx_work_fn ; 
 int /*<<< orphan*/ * ps2_gpio_write ; 
 int /*<<< orphan*/  serio_register_port (struct serio*) ; 
 int /*<<< orphan*/  strlcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int ps2_gpio_probe(struct platform_device *pdev)
{
	struct ps2_gpio_data *drvdata;
	struct serio *serio;
	struct device *dev = &pdev->dev;
	int error;

	drvdata = devm_kzalloc(dev, sizeof(struct ps2_gpio_data), GFP_KERNEL);
	serio = kzalloc(sizeof(struct serio), GFP_KERNEL);
	if (!drvdata || !serio) {
		error = -ENOMEM;
		goto err_free_serio;
	}

	error = ps2_gpio_get_props(dev, drvdata);
	if (error)
		goto err_free_serio;

	if (gpiod_cansleep(drvdata->gpio_data) ||
	    gpiod_cansleep(drvdata->gpio_clk)) {
		dev_err(dev, "GPIO data or clk are connected via slow bus\n");
		error = -EINVAL;
		goto err_free_serio;
	}

	drvdata->irq = platform_get_irq(pdev, 0);
	if (drvdata->irq < 0) {
		error = drvdata->irq;
		goto err_free_serio;
	}

	error = devm_request_irq(dev, drvdata->irq, ps2_gpio_irq,
				 IRQF_NO_THREAD, DRIVER_NAME, drvdata);
	if (error) {
		dev_err(dev, "failed to request irq %d: %d\n",
			drvdata->irq, error);
		goto err_free_serio;
	}

	/* Keep irq disabled until serio->open is called. */
	disable_irq(drvdata->irq);

	serio->id.type = SERIO_8042;
	serio->open = ps2_gpio_open;
	serio->close = ps2_gpio_close;
	/* Write can be enabled in platform/dt data, but possibly it will not
	 * work because of the tough timings.
	 */
	serio->write = drvdata->write_enable ? ps2_gpio_write : NULL;
	serio->port_data = drvdata;
	serio->dev.parent = dev;
	strlcpy(serio->name, dev_name(dev), sizeof(serio->name));
	strlcpy(serio->phys, dev_name(dev), sizeof(serio->phys));

	drvdata->serio = serio;
	drvdata->dev = dev;
	drvdata->mode = PS2_MODE_RX;

	/* Tx count always starts at 1, as the start bit is sent implicitly by
	 * host-to-device communication initialization.
	 */
	drvdata->tx_cnt = 1;

	INIT_DELAYED_WORK(&drvdata->tx_work, ps2_gpio_tx_work_fn);
	init_completion(&drvdata->tx_done);
	mutex_init(&drvdata->tx_mutex);

	serio_register_port(serio);
	platform_set_drvdata(pdev, drvdata);

	return 0;	/* success */

err_free_serio:
	kfree(serio);
	return error;
}