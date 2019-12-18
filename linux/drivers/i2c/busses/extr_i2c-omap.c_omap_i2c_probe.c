#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_20__   TYPE_2__ ;
typedef  struct TYPE_19__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
typedef  int u32 ;
typedef  int u16 ;
struct resource {int dummy; } ;
struct TYPE_20__ {struct device_node* of_node; } ;
struct platform_device {TYPE_2__ dev; int /*<<< orphan*/  id; int /*<<< orphan*/  name; } ;
struct TYPE_19__ {struct device_node* of_node; TYPE_2__* parent; } ;
struct i2c_adapter {int /*<<< orphan*/  nr; int /*<<< orphan*/ * bus_recovery_info; TYPE_1__ dev; int /*<<< orphan*/ * quirks; int /*<<< orphan*/ * algo; int /*<<< orphan*/  name; int /*<<< orphan*/  class; int /*<<< orphan*/  owner; } ;
struct omap_i2c_dev {int flags; int speed; int irq; int reg_shift; int scheme; int rev; int fifo_size; int b_hw; int latency; TYPE_2__* dev; struct i2c_adapter adapter; int /*<<< orphan*/ * set_mpu_wkup_lat; int /*<<< orphan*/  errata; int /*<<< orphan*/ * regs; scalar_t__ base; int /*<<< orphan*/  cmd_complete; } ;
struct omap_i2c_bus_platform_data {int flags; int clkrate; int /*<<< orphan*/ * set_mpu_wkup_lat; } ;
struct of_device_id {struct omap_i2c_bus_platform_data* data; } ;
struct device_node {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  I2C_CLASS_DEPRECATED ; 
 int /*<<< orphan*/  I2C_OMAP_ERRATA_I207 ; 
 int /*<<< orphan*/  I2C_OMAP_ERRATA_I462 ; 
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 int IRQF_NO_SUSPEND ; 
 int IRQF_ONESHOT ; 
 scalar_t__ IS_ERR (scalar_t__) ; 
 int /*<<< orphan*/  OMAP_I2C_BUFSTAT_REG ; 
 int /*<<< orphan*/  OMAP_I2C_CON_REG ; 
 int OMAP_I2C_FLAG_BUS_SHIFT__SHIFT ; 
 int OMAP_I2C_FLAG_NO_FIFO ; 
 int /*<<< orphan*/  OMAP_I2C_IP_V2_REVNB_LO ; 
 scalar_t__ OMAP_I2C_OMAP1_REV_2 ; 
 int /*<<< orphan*/  OMAP_I2C_PM_TIMEOUT ; 
 scalar_t__ OMAP_I2C_REV_ON_2430 ; 
 scalar_t__ OMAP_I2C_REV_ON_3430_3530 ; 
 scalar_t__ OMAP_I2C_REV_ON_3630 ; 
 scalar_t__ OMAP_I2C_REV_ON_4430_PLUS ; 
 int /*<<< orphan*/  OMAP_I2C_REV_REG ; 
 int OMAP_I2C_REV_SCHEME_0_MAJOR (int) ; 
 int OMAP_I2C_REV_SCHEME_1_MAJOR (int) ; 
 int OMAP_I2C_REV_SCHEME_1_MINOR (int) ; 
 int OMAP_I2C_SCHEME (int) ; 
#define  OMAP_I2C_SCHEME_0 129 
#define  OMAP_I2C_SCHEME_1 128 
 int PTR_ERR (scalar_t__) ; 
 int /*<<< orphan*/  THIS_MODULE ; 
 int /*<<< orphan*/  dev_err (TYPE_2__*,char*,...) ; 
 struct omap_i2c_bus_platform_data* dev_get_platdata (TYPE_2__*) ; 
 int /*<<< orphan*/  dev_info (TYPE_2__*,char*,int /*<<< orphan*/ ,int,int,int) ; 
 scalar_t__ devm_ioremap_resource (TYPE_2__*,struct resource*) ; 
 struct omap_i2c_dev* devm_kzalloc (TYPE_2__*,int,int /*<<< orphan*/ ) ; 
 int devm_request_irq (TYPE_2__*,int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,struct omap_i2c_dev*) ; 
 int devm_request_threaded_irq (TYPE_2__*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,struct omap_i2c_dev*) ; 
 int i2c_add_numbered_adapter (struct i2c_adapter*) ; 
 int /*<<< orphan*/  i2c_set_adapdata (struct i2c_adapter*,struct omap_i2c_dev*) ; 
 int /*<<< orphan*/  init_completion (int /*<<< orphan*/ *) ; 
 struct of_device_id* of_match_device (int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  of_match_ptr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  of_property_read_u32 (struct device_node*,char*,int*) ; 
 int /*<<< orphan*/  omap_i2c_algo ; 
 int /*<<< orphan*/  omap_i2c_bus_recovery_info ; 
 int /*<<< orphan*/  omap_i2c_init (struct omap_i2c_dev*) ; 
 int /*<<< orphan*/  omap_i2c_isr ; 
 int /*<<< orphan*/  omap_i2c_isr_thread ; 
 int /*<<< orphan*/  omap_i2c_of_match ; 
 int /*<<< orphan*/  omap_i2c_omap1_isr ; 
 int /*<<< orphan*/  omap_i2c_quirks ; 
 int omap_i2c_read_reg (struct omap_i2c_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  omap_i2c_write_reg (struct omap_i2c_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int platform_get_irq (struct platform_device*,int /*<<< orphan*/ ) ; 
 struct resource* platform_get_resource (struct platform_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct omap_i2c_dev*) ; 
 int /*<<< orphan*/  pm_runtime_disable (TYPE_2__*) ; 
 int /*<<< orphan*/  pm_runtime_dont_use_autosuspend (TYPE_2__*) ; 
 int /*<<< orphan*/  pm_runtime_enable (TYPE_2__*) ; 
 int pm_runtime_get_sync (TYPE_2__*) ; 
 int /*<<< orphan*/  pm_runtime_mark_last_busy (TYPE_2__*) ; 
 int /*<<< orphan*/  pm_runtime_put_autosuspend (TYPE_2__*) ; 
 int /*<<< orphan*/  pm_runtime_put_sync (TYPE_2__*) ; 
 int /*<<< orphan*/  pm_runtime_set_autosuspend_delay (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm_runtime_use_autosuspend (TYPE_2__*) ; 
 int readw_relaxed (scalar_t__) ; 
 scalar_t__ reg_map_ip_v1 ; 
 scalar_t__ reg_map_ip_v2 ; 
 int /*<<< orphan*/  strlcpy (int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static int
omap_i2c_probe(struct platform_device *pdev)
{
	struct omap_i2c_dev	*omap;
	struct i2c_adapter	*adap;
	struct resource		*mem;
	const struct omap_i2c_bus_platform_data *pdata =
		dev_get_platdata(&pdev->dev);
	struct device_node	*node = pdev->dev.of_node;
	const struct of_device_id *match;
	int irq;
	int r;
	u32 rev;
	u16 minor, major;

	irq = platform_get_irq(pdev, 0);
	if (irq < 0) {
		dev_err(&pdev->dev, "no irq resource?\n");
		return irq;
	}

	omap = devm_kzalloc(&pdev->dev, sizeof(struct omap_i2c_dev), GFP_KERNEL);
	if (!omap)
		return -ENOMEM;

	mem = platform_get_resource(pdev, IORESOURCE_MEM, 0);
	omap->base = devm_ioremap_resource(&pdev->dev, mem);
	if (IS_ERR(omap->base))
		return PTR_ERR(omap->base);

	match = of_match_device(of_match_ptr(omap_i2c_of_match), &pdev->dev);
	if (match) {
		u32 freq = 100000; /* default to 100000 Hz */

		pdata = match->data;
		omap->flags = pdata->flags;

		of_property_read_u32(node, "clock-frequency", &freq);
		/* convert DT freq value in Hz into kHz for speed */
		omap->speed = freq / 1000;
	} else if (pdata != NULL) {
		omap->speed = pdata->clkrate;
		omap->flags = pdata->flags;
		omap->set_mpu_wkup_lat = pdata->set_mpu_wkup_lat;
	}

	omap->dev = &pdev->dev;
	omap->irq = irq;

	platform_set_drvdata(pdev, omap);
	init_completion(&omap->cmd_complete);

	omap->reg_shift = (omap->flags >> OMAP_I2C_FLAG_BUS_SHIFT__SHIFT) & 3;

	pm_runtime_enable(omap->dev);
	pm_runtime_set_autosuspend_delay(omap->dev, OMAP_I2C_PM_TIMEOUT);
	pm_runtime_use_autosuspend(omap->dev);

	r = pm_runtime_get_sync(omap->dev);
	if (r < 0)
		goto err_free_mem;

	/*
	 * Read the Rev hi bit-[15:14] ie scheme this is 1 indicates ver2.
	 * On omap1/3/2 Offset 4 is IE Reg the bit [15:14] is 0 at reset.
	 * Also since the omap_i2c_read_reg uses reg_map_ip_* a
	 * readw_relaxed is done.
	 */
	rev = readw_relaxed(omap->base + 0x04);

	omap->scheme = OMAP_I2C_SCHEME(rev);
	switch (omap->scheme) {
	case OMAP_I2C_SCHEME_0:
		omap->regs = (u8 *)reg_map_ip_v1;
		omap->rev = omap_i2c_read_reg(omap, OMAP_I2C_REV_REG);
		minor = OMAP_I2C_REV_SCHEME_0_MAJOR(omap->rev);
		major = OMAP_I2C_REV_SCHEME_0_MAJOR(omap->rev);
		break;
	case OMAP_I2C_SCHEME_1:
		/* FALLTHROUGH */
	default:
		omap->regs = (u8 *)reg_map_ip_v2;
		rev = (rev << 16) |
			omap_i2c_read_reg(omap, OMAP_I2C_IP_V2_REVNB_LO);
		minor = OMAP_I2C_REV_SCHEME_1_MINOR(rev);
		major = OMAP_I2C_REV_SCHEME_1_MAJOR(rev);
		omap->rev = rev;
	}

	omap->errata = 0;

	if (omap->rev >= OMAP_I2C_REV_ON_2430 &&
			omap->rev < OMAP_I2C_REV_ON_4430_PLUS)
		omap->errata |= I2C_OMAP_ERRATA_I207;

	if (omap->rev <= OMAP_I2C_REV_ON_3430_3530)
		omap->errata |= I2C_OMAP_ERRATA_I462;

	if (!(omap->flags & OMAP_I2C_FLAG_NO_FIFO)) {
		u16 s;

		/* Set up the fifo size - Get total size */
		s = (omap_i2c_read_reg(omap, OMAP_I2C_BUFSTAT_REG) >> 14) & 0x3;
		omap->fifo_size = 0x8 << s;

		/*
		 * Set up notification threshold as half the total available
		 * size. This is to ensure that we can handle the status on int
		 * call back latencies.
		 */

		omap->fifo_size = (omap->fifo_size / 2);

		if (omap->rev < OMAP_I2C_REV_ON_3630)
			omap->b_hw = 1; /* Enable hardware fixes */

		/* calculate wakeup latency constraint for MPU */
		if (omap->set_mpu_wkup_lat != NULL)
			omap->latency = (1000000 * omap->fifo_size) /
				       (1000 * omap->speed / 8);
	}

	/* reset ASAP, clearing any IRQs */
	omap_i2c_init(omap);

	if (omap->rev < OMAP_I2C_OMAP1_REV_2)
		r = devm_request_irq(&pdev->dev, omap->irq, omap_i2c_omap1_isr,
				IRQF_NO_SUSPEND, pdev->name, omap);
	else
		r = devm_request_threaded_irq(&pdev->dev, omap->irq,
				omap_i2c_isr, omap_i2c_isr_thread,
				IRQF_NO_SUSPEND | IRQF_ONESHOT,
				pdev->name, omap);

	if (r) {
		dev_err(omap->dev, "failure requesting irq %i\n", omap->irq);
		goto err_unuse_clocks;
	}

	adap = &omap->adapter;
	i2c_set_adapdata(adap, omap);
	adap->owner = THIS_MODULE;
	adap->class = I2C_CLASS_DEPRECATED;
	strlcpy(adap->name, "OMAP I2C adapter", sizeof(adap->name));
	adap->algo = &omap_i2c_algo;
	adap->quirks = &omap_i2c_quirks;
	adap->dev.parent = &pdev->dev;
	adap->dev.of_node = pdev->dev.of_node;
	adap->bus_recovery_info = &omap_i2c_bus_recovery_info;

	/* i2c device drivers may be active on return from add_adapter() */
	adap->nr = pdev->id;
	r = i2c_add_numbered_adapter(adap);
	if (r)
		goto err_unuse_clocks;

	dev_info(omap->dev, "bus %d rev%d.%d at %d kHz\n", adap->nr,
		 major, minor, omap->speed);

	pm_runtime_mark_last_busy(omap->dev);
	pm_runtime_put_autosuspend(omap->dev);

	return 0;

err_unuse_clocks:
	omap_i2c_write_reg(omap, OMAP_I2C_CON_REG, 0);
	pm_runtime_dont_use_autosuspend(omap->dev);
	pm_runtime_put_sync(omap->dev);
	pm_runtime_disable(&pdev->dev);
err_free_mem:

	return r;
}