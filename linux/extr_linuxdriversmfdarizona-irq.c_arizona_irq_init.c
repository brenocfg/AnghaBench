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
struct regmap_irq_chip {int dummy; } ;
struct irq_data {int dummy; } ;
struct TYPE_2__ {int irq_flags; int irq_gpio; } ;
struct arizona {int ctrlif_error; int type; int irq; int /*<<< orphan*/  virq; int /*<<< orphan*/  aod_irq_chip; int /*<<< orphan*/  irq_chip; int /*<<< orphan*/  dev; TYPE_1__ pdata; int /*<<< orphan*/  regmap; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARIZONA_AOD_IRQ_INDEX ; 
 int /*<<< orphan*/  ARIZONA_IRQ_BOOT_DONE ; 
 int /*<<< orphan*/  ARIZONA_IRQ_CTRLIF_ERR ; 
 int /*<<< orphan*/  ARIZONA_IRQ_CTRL_1 ; 
 int /*<<< orphan*/  ARIZONA_IRQ_POL ; 
 int /*<<< orphan*/  ARIZONA_MAIN_IRQ_INDEX ; 
 int /*<<< orphan*/  ARIZONA_WAKE_CONTROL ; 
 int /*<<< orphan*/  BUG_ON (int /*<<< orphan*/ ) ; 
 int EINVAL ; 
 int /*<<< orphan*/  GPIOF_IN ; 
 int IRQF_ONESHOT ; 
#define  IRQF_TRIGGER_FALLING 132 
#define  IRQF_TRIGGER_HIGH 131 
#define  IRQF_TRIGGER_LOW 130 
#define  IRQF_TRIGGER_RISING 129 
#define  IRQ_TYPE_NONE 128 
 int /*<<< orphan*/  arizona_boot_done ; 
 int /*<<< orphan*/  arizona_ctrlif_err ; 
 int /*<<< orphan*/  arizona_domain_ops ; 
 int /*<<< orphan*/  arizona_free_irq (struct arizona*,int /*<<< orphan*/ ,struct arizona*) ; 
 int /*<<< orphan*/  arizona_irq_thread ; 
 int arizona_request_irq (struct arizona*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,struct arizona*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ ,char*,int,int,int) ; 
 int devm_gpio_request_one (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  free_irq (int,struct arizona*) ; 
 int gpio_to_irq (int) ; 
 unsigned int irq_create_mapping (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  irq_dispose_mapping (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  irq_domain_add_linear (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,struct arizona*) ; 
 int /*<<< orphan*/  irq_domain_remove (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  irq_find_mapping (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct irq_data* irq_get_irq_data (int) ; 
 int irqd_get_trigger_type (struct irq_data*) ; 
 int regmap_add_irq_chip (int /*<<< orphan*/ ,unsigned int,int,int /*<<< orphan*/ ,struct regmap_irq_chip const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  regmap_del_irq_chip (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  regmap_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int request_threaded_irq (int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,char*,struct arizona*) ; 

int arizona_irq_init(struct arizona *arizona)
{
	int flags = IRQF_ONESHOT;
	int ret;
	const struct regmap_irq_chip *aod, *irq;
	struct irq_data *irq_data;
	unsigned int virq;

	arizona->ctrlif_error = true;

	switch (arizona->type) {
#ifdef CONFIG_MFD_WM5102
	case WM5102:
		aod = &wm5102_aod;
		irq = &wm5102_irq;

		arizona->ctrlif_error = false;
		break;
#endif
#ifdef CONFIG_MFD_WM5110
	case WM5110:
	case WM8280:
		aod = &wm5110_aod;

		switch (arizona->rev) {
		case 0 ... 2:
			irq = &wm5110_irq;
			break;
		default:
			irq = &wm5110_revd_irq;
			break;
		}

		arizona->ctrlif_error = false;
		break;
#endif
#ifdef CONFIG_MFD_CS47L24
	case WM1831:
	case CS47L24:
		aod = NULL;
		irq = &cs47l24_irq;

		arizona->ctrlif_error = false;
		break;
#endif
#ifdef CONFIG_MFD_WM8997
	case WM8997:
		aod = &wm8997_aod;
		irq = &wm8997_irq;

		arizona->ctrlif_error = false;
		break;
#endif
#ifdef CONFIG_MFD_WM8998
	case WM8998:
	case WM1814:
		aod = &wm8998_aod;
		irq = &wm8998_irq;

		arizona->ctrlif_error = false;
		break;
#endif
	default:
		BUG_ON("Unknown Arizona class device" == NULL);
		return -EINVAL;
	}

	/* Disable all wake sources by default */
	regmap_write(arizona->regmap, ARIZONA_WAKE_CONTROL, 0);

	/* Read the flags from the interrupt controller if not specified */
	if (!arizona->pdata.irq_flags) {
		irq_data = irq_get_irq_data(arizona->irq);
		if (!irq_data) {
			dev_err(arizona->dev, "Invalid IRQ: %d\n",
				arizona->irq);
			return -EINVAL;
		}

		arizona->pdata.irq_flags = irqd_get_trigger_type(irq_data);
		switch (arizona->pdata.irq_flags) {
		case IRQF_TRIGGER_LOW:
		case IRQF_TRIGGER_HIGH:
		case IRQF_TRIGGER_RISING:
		case IRQF_TRIGGER_FALLING:
			break;

		case IRQ_TYPE_NONE:
		default:
			/* Device default */
			arizona->pdata.irq_flags = IRQF_TRIGGER_LOW;
			break;
		}
	}

	if (arizona->pdata.irq_flags & (IRQF_TRIGGER_HIGH |
					IRQF_TRIGGER_RISING)) {
		ret = regmap_update_bits(arizona->regmap, ARIZONA_IRQ_CTRL_1,
					 ARIZONA_IRQ_POL, 0);
		if (ret != 0) {
			dev_err(arizona->dev, "Couldn't set IRQ polarity: %d\n",
				ret);
			goto err;
		}
	}

	flags |= arizona->pdata.irq_flags;

	/* Allocate a virtual IRQ domain to distribute to the regmap domains */
	arizona->virq = irq_domain_add_linear(NULL, 2, &arizona_domain_ops,
					      arizona);
	if (!arizona->virq) {
		dev_err(arizona->dev, "Failed to add core IRQ domain\n");
		ret = -EINVAL;
		goto err;
	}

	if (aod) {
		virq = irq_create_mapping(arizona->virq, ARIZONA_AOD_IRQ_INDEX);
		if (!virq) {
			dev_err(arizona->dev, "Failed to map AOD IRQs\n");
			ret = -EINVAL;
			goto err_domain;
		}

		ret = regmap_add_irq_chip(arizona->regmap, virq, IRQF_ONESHOT,
					  0, aod, &arizona->aod_irq_chip);
		if (ret != 0) {
			dev_err(arizona->dev,
				"Failed to add AOD IRQs: %d\n", ret);
			goto err_map_aod;
		}
	}

	virq = irq_create_mapping(arizona->virq, ARIZONA_MAIN_IRQ_INDEX);
	if (!virq) {
		dev_err(arizona->dev, "Failed to map main IRQs\n");
		ret = -EINVAL;
		goto err_aod;
	}

	ret = regmap_add_irq_chip(arizona->regmap, virq, IRQF_ONESHOT,
				  0, irq, &arizona->irq_chip);
	if (ret != 0) {
		dev_err(arizona->dev, "Failed to add main IRQs: %d\n", ret);
		goto err_map_main_irq;
	}

	/* Used to emulate edge trigger and to work around broken pinmux */
	if (arizona->pdata.irq_gpio) {
		if (gpio_to_irq(arizona->pdata.irq_gpio) != arizona->irq) {
			dev_warn(arizona->dev, "IRQ %d is not GPIO %d (%d)\n",
				 arizona->irq, arizona->pdata.irq_gpio,
				 gpio_to_irq(arizona->pdata.irq_gpio));
			arizona->irq = gpio_to_irq(arizona->pdata.irq_gpio);
		}

		ret = devm_gpio_request_one(arizona->dev,
					    arizona->pdata.irq_gpio,
					    GPIOF_IN, "arizona IRQ");
		if (ret != 0) {
			dev_err(arizona->dev,
				"Failed to request IRQ GPIO %d:: %d\n",
				arizona->pdata.irq_gpio, ret);
			arizona->pdata.irq_gpio = 0;
		}
	}

	ret = request_threaded_irq(arizona->irq, NULL, arizona_irq_thread,
				   flags, "arizona", arizona);

	if (ret != 0) {
		dev_err(arizona->dev, "Failed to request primary IRQ %d: %d\n",
			arizona->irq, ret);
		goto err_main_irq;
	}

	/* Make sure the boot done IRQ is unmasked for resumes */
	ret = arizona_request_irq(arizona, ARIZONA_IRQ_BOOT_DONE, "Boot done",
				  arizona_boot_done, arizona);
	if (ret != 0) {
		dev_err(arizona->dev, "Failed to request boot done %d: %d\n",
			arizona->irq, ret);
		goto err_boot_done;
	}

	/* Handle control interface errors in the core */
	if (arizona->ctrlif_error) {
		ret = arizona_request_irq(arizona, ARIZONA_IRQ_CTRLIF_ERR,
					  "Control interface error",
					  arizona_ctrlif_err, arizona);
		if (ret != 0) {
			dev_err(arizona->dev,
				"Failed to request CTRLIF_ERR %d: %d\n",
				arizona->irq, ret);
			goto err_ctrlif;
		}
	}

	return 0;

err_ctrlif:
	arizona_free_irq(arizona, ARIZONA_IRQ_BOOT_DONE, arizona);
err_boot_done:
	free_irq(arizona->irq, arizona);
err_main_irq:
	regmap_del_irq_chip(irq_find_mapping(arizona->virq,
					     ARIZONA_MAIN_IRQ_INDEX),
			    arizona->irq_chip);
err_map_main_irq:
	irq_dispose_mapping(irq_find_mapping(arizona->virq,
					     ARIZONA_MAIN_IRQ_INDEX));
err_aod:
	regmap_del_irq_chip(irq_find_mapping(arizona->virq,
					     ARIZONA_AOD_IRQ_INDEX),
			    arizona->aod_irq_chip);
err_map_aod:
	irq_dispose_mapping(irq_find_mapping(arizona->virq,
					     ARIZONA_AOD_IRQ_INDEX));
err_domain:
	irq_domain_remove(arizona->virq);
err:
	return ret;
}