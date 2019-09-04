#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
struct resource {int dummy; } ;
struct TYPE_13__ {int /*<<< orphan*/  of_node; } ;
struct platform_device {TYPE_2__ dev; int /*<<< orphan*/  name; } ;
struct ocores_i2c_platform_data {int reg_io_width; int big_endian; int num_devices; scalar_t__ devices; int /*<<< orphan*/  clock_khz; int /*<<< orphan*/  reg_shift; } ;
struct TYPE_12__ {int /*<<< orphan*/  of_node; TYPE_2__* parent; } ;
struct TYPE_14__ {TYPE_1__ dev; } ;
struct ocores_i2c {int reg_io_width; int bus_clock_khz; int /*<<< orphan*/  clk; TYPE_3__ adap; int /*<<< orphan*/  wait; int /*<<< orphan*/  getreg; int /*<<< orphan*/  setreg; int /*<<< orphan*/  ip_clock_khz; int /*<<< orphan*/  reg_shift; int /*<<< orphan*/  base; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (TYPE_2__*,char*,...) ; 
 struct ocores_i2c_platform_data* dev_get_platdata (TYPE_2__*) ; 
 int /*<<< orphan*/  devm_ioremap_resource (TYPE_2__*,struct resource*) ; 
 struct ocores_i2c* devm_kzalloc (TYPE_2__*,int,int /*<<< orphan*/ ) ; 
 int devm_request_irq (TYPE_2__*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct ocores_i2c*) ; 
 int i2c_add_adapter (TYPE_3__*) ; 
 int /*<<< orphan*/  i2c_new_device (TYPE_3__*,scalar_t__) ; 
 int /*<<< orphan*/  i2c_set_adapdata (TYPE_3__*,struct ocores_i2c*) ; 
 int /*<<< orphan*/  init_waitqueue_head (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  oc_getreg_16 ; 
 int /*<<< orphan*/  oc_getreg_16be ; 
 int /*<<< orphan*/  oc_getreg_32 ; 
 int /*<<< orphan*/  oc_getreg_32be ; 
 int /*<<< orphan*/  oc_getreg_8 ; 
 int /*<<< orphan*/  oc_setreg_16 ; 
 int /*<<< orphan*/  oc_setreg_16be ; 
 int /*<<< orphan*/  oc_setreg_32 ; 
 int /*<<< orphan*/  oc_setreg_32be ; 
 int /*<<< orphan*/  oc_setreg_8 ; 
 TYPE_3__ ocores_adapter ; 
 int ocores_i2c_of_probe (struct platform_device*,struct ocores_i2c*) ; 
 int ocores_init (TYPE_2__*,struct ocores_i2c*) ; 
 int /*<<< orphan*/  ocores_isr ; 
 int of_device_is_big_endian (int /*<<< orphan*/ ) ; 
 int platform_get_irq (struct platform_device*,int /*<<< orphan*/ ) ; 
 struct resource* platform_get_resource (struct platform_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct ocores_i2c*) ; 

__attribute__((used)) static int ocores_i2c_probe(struct platform_device *pdev)
{
	struct ocores_i2c *i2c;
	struct ocores_i2c_platform_data *pdata;
	struct resource *res;
	int irq;
	int ret;
	int i;

	irq = platform_get_irq(pdev, 0);
	if (irq < 0)
		return irq;

	i2c = devm_kzalloc(&pdev->dev, sizeof(*i2c), GFP_KERNEL);
	if (!i2c)
		return -ENOMEM;

	res = platform_get_resource(pdev, IORESOURCE_MEM, 0);
	i2c->base = devm_ioremap_resource(&pdev->dev, res);
	if (IS_ERR(i2c->base))
		return PTR_ERR(i2c->base);

	pdata = dev_get_platdata(&pdev->dev);
	if (pdata) {
		i2c->reg_shift = pdata->reg_shift;
		i2c->reg_io_width = pdata->reg_io_width;
		i2c->ip_clock_khz = pdata->clock_khz;
		i2c->bus_clock_khz = 100;
	} else {
		ret = ocores_i2c_of_probe(pdev, i2c);
		if (ret)
			return ret;
	}

	if (i2c->reg_io_width == 0)
		i2c->reg_io_width = 1; /* Set to default value */

	if (!i2c->setreg || !i2c->getreg) {
		bool be = pdata ? pdata->big_endian :
			of_device_is_big_endian(pdev->dev.of_node);

		switch (i2c->reg_io_width) {
		case 1:
			i2c->setreg = oc_setreg_8;
			i2c->getreg = oc_getreg_8;
			break;

		case 2:
			i2c->setreg = be ? oc_setreg_16be : oc_setreg_16;
			i2c->getreg = be ? oc_getreg_16be : oc_getreg_16;
			break;

		case 4:
			i2c->setreg = be ? oc_setreg_32be : oc_setreg_32;
			i2c->getreg = be ? oc_getreg_32be : oc_getreg_32;
			break;

		default:
			dev_err(&pdev->dev, "Unsupported I/O width (%d)\n",
				i2c->reg_io_width);
			ret = -EINVAL;
			goto err_clk;
		}
	}

	ret = ocores_init(&pdev->dev, i2c);
	if (ret)
		goto err_clk;

	init_waitqueue_head(&i2c->wait);
	ret = devm_request_irq(&pdev->dev, irq, ocores_isr, 0,
			       pdev->name, i2c);
	if (ret) {
		dev_err(&pdev->dev, "Cannot claim IRQ\n");
		goto err_clk;
	}

	/* hook up driver to tree */
	platform_set_drvdata(pdev, i2c);
	i2c->adap = ocores_adapter;
	i2c_set_adapdata(&i2c->adap, i2c);
	i2c->adap.dev.parent = &pdev->dev;
	i2c->adap.dev.of_node = pdev->dev.of_node;

	/* add i2c adapter to i2c tree */
	ret = i2c_add_adapter(&i2c->adap);
	if (ret)
		goto err_clk;

	/* add in known devices to the bus */
	if (pdata) {
		for (i = 0; i < pdata->num_devices; i++)
			i2c_new_device(&i2c->adap, pdata->devices + i);
	}

	return 0;

err_clk:
	clk_disable_unprepare(i2c->clk);
	return ret;
}