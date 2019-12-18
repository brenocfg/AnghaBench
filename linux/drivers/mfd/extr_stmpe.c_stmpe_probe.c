#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
typedef  void* u32 ;
struct stmpe_platform_data {int irq_trigger; int /*<<< orphan*/  irq_gpio; scalar_t__ irq_over_gpio; } ;
struct stmpe_client_info {int irq; TYPE_3__* dev; int /*<<< orphan*/  (* init ) (struct stmpe*) ;int /*<<< orphan*/  client; } ;
struct stmpe {int partnum; int irq; TYPE_3__* dev; TYPE_1__* variant; void* vio; void* vcc; int /*<<< orphan*/  num_gpios; int /*<<< orphan*/  regs; struct stmpe_client_info* ci; struct stmpe_platform_data* pdata; int /*<<< orphan*/  client; void* adc_freq; void* ref_sel; void* mod_12b; void* sample_time; int /*<<< orphan*/  lock; int /*<<< orphan*/  irq_lock; } ;
struct device_node {int dummy; } ;
typedef  enum stmpe_partnum { ____Placeholder_stmpe_partnum } stmpe_partnum ;
struct TYPE_13__ {struct device_node* of_node; } ;
struct TYPE_12__ {int /*<<< orphan*/  name; int /*<<< orphan*/  num_gpios; int /*<<< orphan*/  regs; } ;

/* Variables and functions */
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  GPIOF_DIR_IN ; 
 int IRQF_ONESHOT ; 
 int IRQF_TRIGGER_NONE ; 
 int /*<<< orphan*/  IS_ERR (void*) ; 
 int /*<<< orphan*/  dev_err (TYPE_3__*,char*,...) ; 
 int /*<<< orphan*/  dev_info (TYPE_3__*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_set_drvdata (TYPE_3__*,struct stmpe*) ; 
 int /*<<< orphan*/  dev_warn (TYPE_3__*,char*) ; 
 int devm_gpio_request_one (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 void* devm_kzalloc (TYPE_3__*,int,int /*<<< orphan*/ ) ; 
 void* devm_regulator_get_optional (TYPE_3__*,char*) ; 
 int devm_request_threaded_irq (TYPE_3__*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,char*,struct stmpe*) ; 
 int gpio_to_irq (int /*<<< orphan*/ ) ; 
 int irq_get_trigger_type (int) ; 
 int /*<<< orphan*/  mfd_remove_devices (TYPE_3__*) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * of_find_property (struct device_node*,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  of_property_read_u32 (struct device_node*,char*,void**) ; 
 int regulator_enable (void*) ; 
 int stmpe_chip_init (struct stmpe*) ; 
 int stmpe_devices_init (struct stmpe*) ; 
 int /*<<< orphan*/  stmpe_irq ; 
 int stmpe_irq_init (struct stmpe*,struct device_node*) ; 
 TYPE_1__** stmpe_noirq_variant_info ; 
 int /*<<< orphan*/  stmpe_of_probe (struct stmpe_platform_data*,struct device_node*) ; 
 TYPE_1__** stmpe_variant_info ; 
 int /*<<< orphan*/  stub1 (struct stmpe*) ; 

int stmpe_probe(struct stmpe_client_info *ci, enum stmpe_partnum partnum)
{
	struct stmpe_platform_data *pdata;
	struct device_node *np = ci->dev->of_node;
	struct stmpe *stmpe;
	int ret;
	u32 val;

	pdata = devm_kzalloc(ci->dev, sizeof(*pdata), GFP_KERNEL);
	if (!pdata)
		return -ENOMEM;

	stmpe_of_probe(pdata, np);

	if (of_find_property(np, "interrupts", NULL) == NULL)
		ci->irq = -1;

	stmpe = devm_kzalloc(ci->dev, sizeof(struct stmpe), GFP_KERNEL);
	if (!stmpe)
		return -ENOMEM;

	mutex_init(&stmpe->irq_lock);
	mutex_init(&stmpe->lock);

	if (!of_property_read_u32(np, "st,sample-time", &val))
		stmpe->sample_time = val;
	if (!of_property_read_u32(np, "st,mod-12b", &val))
		stmpe->mod_12b = val;
	if (!of_property_read_u32(np, "st,ref-sel", &val))
		stmpe->ref_sel = val;
	if (!of_property_read_u32(np, "st,adc-freq", &val))
		stmpe->adc_freq = val;

	stmpe->dev = ci->dev;
	stmpe->client = ci->client;
	stmpe->pdata = pdata;
	stmpe->ci = ci;
	stmpe->partnum = partnum;
	stmpe->variant = stmpe_variant_info[partnum];
	stmpe->regs = stmpe->variant->regs;
	stmpe->num_gpios = stmpe->variant->num_gpios;
	stmpe->vcc = devm_regulator_get_optional(ci->dev, "vcc");
	if (!IS_ERR(stmpe->vcc)) {
		ret = regulator_enable(stmpe->vcc);
		if (ret)
			dev_warn(ci->dev, "failed to enable VCC supply\n");
	}
	stmpe->vio = devm_regulator_get_optional(ci->dev, "vio");
	if (!IS_ERR(stmpe->vio)) {
		ret = regulator_enable(stmpe->vio);
		if (ret)
			dev_warn(ci->dev, "failed to enable VIO supply\n");
	}
	dev_set_drvdata(stmpe->dev, stmpe);

	if (ci->init)
		ci->init(stmpe);

	if (pdata->irq_over_gpio) {
		ret = devm_gpio_request_one(ci->dev, pdata->irq_gpio,
				GPIOF_DIR_IN, "stmpe");
		if (ret) {
			dev_err(stmpe->dev, "failed to request IRQ GPIO: %d\n",
					ret);
			return ret;
		}

		stmpe->irq = gpio_to_irq(pdata->irq_gpio);
	} else {
		stmpe->irq = ci->irq;
	}

	if (stmpe->irq < 0) {
		/* use alternate variant info for no-irq mode, if supported */
		dev_info(stmpe->dev,
			"%s configured in no-irq mode by platform data\n",
			stmpe->variant->name);
		if (!stmpe_noirq_variant_info[stmpe->partnum]) {
			dev_err(stmpe->dev,
				"%s does not support no-irq mode!\n",
				stmpe->variant->name);
			return -ENODEV;
		}
		stmpe->variant = stmpe_noirq_variant_info[stmpe->partnum];
	} else if (pdata->irq_trigger == IRQF_TRIGGER_NONE) {
		pdata->irq_trigger = irq_get_trigger_type(stmpe->irq);
	}

	ret = stmpe_chip_init(stmpe);
	if (ret)
		return ret;

	if (stmpe->irq >= 0) {
		ret = stmpe_irq_init(stmpe, np);
		if (ret)
			return ret;

		ret = devm_request_threaded_irq(ci->dev, stmpe->irq, NULL,
				stmpe_irq, pdata->irq_trigger | IRQF_ONESHOT,
				"stmpe", stmpe);
		if (ret) {
			dev_err(stmpe->dev, "failed to request IRQ: %d\n",
					ret);
			return ret;
		}
	}

	ret = stmpe_devices_init(stmpe);
	if (!ret)
		return 0;

	dev_err(stmpe->dev, "failed to add children\n");
	mfd_remove_devices(stmpe->dev);

	return ret;
}