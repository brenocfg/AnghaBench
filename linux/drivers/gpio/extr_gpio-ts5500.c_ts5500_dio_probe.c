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
struct TYPE_4__ {char const* label; int base; void* ngpio; int /*<<< orphan*/  to_irq; int /*<<< orphan*/  set; int /*<<< orphan*/  get; int /*<<< orphan*/  direction_output; int /*<<< orphan*/  direction_input; struct device* parent; int /*<<< orphan*/  owner; } ;
struct ts5500_priv {char const* hwirq; TYPE_2__ gpio_chip; int /*<<< orphan*/  lock; void* pinout; } ;
struct resource {char const* start; } ;
struct device {int dummy; } ;
struct platform_device {struct device dev; } ;
typedef  enum ts5500_blocks { ____Placeholder_ts5500_blocks } ts5500_blocks ;
struct TYPE_3__ {int driver_data; } ;

/* Variables and functions */
 void* ARRAY_SIZE (void*) ; 
 int /*<<< orphan*/  BIT (int) ; 
 int EBUSY ; 
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IORESOURCE_IRQ ; 
 int /*<<< orphan*/  THIS_MODULE ; 
#define  TS5500_DIO1 131 
#define  TS5500_DIO2 130 
#define  TS5500_LCD 129 
#define  TS5600_LCD 128 
 int /*<<< orphan*/  dev_err (struct device*,char*,...) ; 
 char* dev_name (struct device*) ; 
 int devm_gpiochip_add_data (struct device*,TYPE_2__*,struct ts5500_priv*) ; 
 struct ts5500_priv* devm_kzalloc (struct device*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  devm_request_region (struct device*,int,int,char const*) ; 
 int hex7d_reserved ; 
 TYPE_1__* platform_get_device_id (struct platform_device*) ; 
 struct resource* platform_get_resource (struct platform_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct ts5500_priv*) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  ts5500_clear_mask (int /*<<< orphan*/ ,int) ; 
 void* ts5500_dio1 ; 
 void* ts5500_dio2 ; 
 int ts5500_enable_irq (struct ts5500_priv*) ; 
 int /*<<< orphan*/  ts5500_gpio_get ; 
 int /*<<< orphan*/  ts5500_gpio_input ; 
 int /*<<< orphan*/  ts5500_gpio_output ; 
 int /*<<< orphan*/  ts5500_gpio_set ; 
 int /*<<< orphan*/  ts5500_gpio_to_irq ; 
 void* ts5500_lcd ; 

__attribute__((used)) static int ts5500_dio_probe(struct platform_device *pdev)
{
	enum ts5500_blocks block = platform_get_device_id(pdev)->driver_data;
	struct device *dev = &pdev->dev;
	const char *name = dev_name(dev);
	struct ts5500_priv *priv;
	struct resource *res;
	unsigned long flags;
	int ret;

	res = platform_get_resource(pdev, IORESOURCE_IRQ, 0);
	if (!res) {
		dev_err(dev, "missing IRQ resource\n");
		return -EINVAL;
	}

	priv = devm_kzalloc(dev, sizeof(struct ts5500_priv), GFP_KERNEL);
	if (!priv)
		return -ENOMEM;

	platform_set_drvdata(pdev, priv);
	priv->hwirq = res->start;
	spin_lock_init(&priv->lock);

	priv->gpio_chip.owner = THIS_MODULE;
	priv->gpio_chip.label = name;
	priv->gpio_chip.parent = dev;
	priv->gpio_chip.direction_input = ts5500_gpio_input;
	priv->gpio_chip.direction_output = ts5500_gpio_output;
	priv->gpio_chip.get = ts5500_gpio_get;
	priv->gpio_chip.set = ts5500_gpio_set;
	priv->gpio_chip.to_irq = ts5500_gpio_to_irq;
	priv->gpio_chip.base = -1;

	switch (block) {
	case TS5500_DIO1:
		priv->pinout = ts5500_dio1;
		priv->gpio_chip.ngpio = ARRAY_SIZE(ts5500_dio1);

		if (!devm_request_region(dev, 0x7a, 3, name)) {
			dev_err(dev, "failed to request %s ports\n", name);
			return -EBUSY;
		}
		break;
	case TS5500_DIO2:
		priv->pinout = ts5500_dio2;
		priv->gpio_chip.ngpio = ARRAY_SIZE(ts5500_dio2);

		if (!devm_request_region(dev, 0x7e, 2, name)) {
			dev_err(dev, "failed to request %s ports\n", name);
			return -EBUSY;
		}

		if (hex7d_reserved)
			break;

		if (!devm_request_region(dev, 0x7d, 1, name)) {
			dev_err(dev, "failed to request %s 7D\n", name);
			return -EBUSY;
		}

		hex7d_reserved = true;
		break;
	case TS5500_LCD:
	case TS5600_LCD:
		priv->pinout = ts5500_lcd;
		priv->gpio_chip.ngpio = ARRAY_SIZE(ts5500_lcd);

		if (!devm_request_region(dev, 0x72, 2, name)) {
			dev_err(dev, "failed to request %s ports\n", name);
			return -EBUSY;
		}

		if (!hex7d_reserved) {
			if (!devm_request_region(dev, 0x7d, 1, name)) {
				dev_err(dev, "failed to request %s 7D\n", name);
				return -EBUSY;
			}

			hex7d_reserved = true;
		}

		/* Ensure usage of LCD port as DIO */
		spin_lock_irqsave(&priv->lock, flags);
		ts5500_clear_mask(BIT(4), 0x7d);
		spin_unlock_irqrestore(&priv->lock, flags);
		break;
	}

	ret = devm_gpiochip_add_data(dev, &priv->gpio_chip, priv);
	if (ret) {
		dev_err(dev, "failed to register the gpio chip\n");
		return ret;
	}

	ret = ts5500_enable_irq(priv);
	if (ret) {
		dev_err(dev, "invalid interrupt %d\n", priv->hwirq);
		return ret;
	}

	return 0;
}