#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct resource {int /*<<< orphan*/  start; } ;
struct TYPE_10__ {scalar_t__ of_node; } ;
struct platform_device {TYPE_1__ dev; } ;
struct gpmc_device {TYPE_1__* dev; scalar_t__ nirqs; int /*<<< orphan*/  irq; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOENT ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  GPMC_CS_NUM ; 
 int GPMC_HAS_MUX_AAD ; 
 int GPMC_HAS_WR_ACCESS ; 
 int GPMC_HAS_WR_DATA_MUX_BUS ; 
 scalar_t__ GPMC_NR_NAND_IRQS ; 
 scalar_t__ GPMC_NR_WAITPINS ; 
 int /*<<< orphan*/  GPMC_REVISION ; 
 int GPMC_REVISION_MAJOR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GPMC_REVISION_MINOR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IORESOURCE_IRQ ; 
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clk_get_rate (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (TYPE_1__*,char*) ; 
 int /*<<< orphan*/  dev_info (TYPE_1__*,char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  devm_clk_get (TYPE_1__*,char*) ; 
 int /*<<< orphan*/  devm_ioremap_resource (TYPE_1__*,struct resource*) ; 
 struct gpmc_device* devm_kzalloc (TYPE_1__*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gpmc_base ; 
 int gpmc_capability ; 
 int /*<<< orphan*/  gpmc_cs_num ; 
 int gpmc_gpio_init (struct gpmc_device*) ; 
 int /*<<< orphan*/  gpmc_l3_clk ; 
 int /*<<< orphan*/  gpmc_mem_exit () ; 
 int /*<<< orphan*/  gpmc_mem_init () ; 
 scalar_t__ gpmc_nr_waitpins ; 
 int gpmc_probe_dt (struct platform_device*) ; 
 int /*<<< orphan*/  gpmc_probe_dt_children (struct platform_device*) ; 
 int /*<<< orphan*/  gpmc_read_reg (int /*<<< orphan*/ ) ; 
 int gpmc_setup_irq (struct gpmc_device*) ; 
 int /*<<< orphan*/  mem_size ; 
 int /*<<< orphan*/  phys_base ; 
 struct resource* platform_get_resource (struct platform_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct gpmc_device*) ; 
 int /*<<< orphan*/  pm_runtime_disable (TYPE_1__*) ; 
 int /*<<< orphan*/  pm_runtime_enable (TYPE_1__*) ; 
 int /*<<< orphan*/  pm_runtime_get_sync (TYPE_1__*) ; 
 int /*<<< orphan*/  pm_runtime_put_sync (TYPE_1__*) ; 
 int /*<<< orphan*/  resource_size (struct resource*) ; 

__attribute__((used)) static int gpmc_probe(struct platform_device *pdev)
{
	int rc;
	u32 l;
	struct resource *res;
	struct gpmc_device *gpmc;

	gpmc = devm_kzalloc(&pdev->dev, sizeof(*gpmc), GFP_KERNEL);
	if (!gpmc)
		return -ENOMEM;

	gpmc->dev = &pdev->dev;
	platform_set_drvdata(pdev, gpmc);

	res = platform_get_resource(pdev, IORESOURCE_MEM, 0);
	if (res == NULL)
		return -ENOENT;

	phys_base = res->start;
	mem_size = resource_size(res);

	gpmc_base = devm_ioremap_resource(&pdev->dev, res);
	if (IS_ERR(gpmc_base))
		return PTR_ERR(gpmc_base);

	res = platform_get_resource(pdev, IORESOURCE_IRQ, 0);
	if (!res) {
		dev_err(&pdev->dev, "Failed to get resource: irq\n");
		return -ENOENT;
	}

	gpmc->irq = res->start;

	gpmc_l3_clk = devm_clk_get(&pdev->dev, "fck");
	if (IS_ERR(gpmc_l3_clk)) {
		dev_err(&pdev->dev, "Failed to get GPMC fck\n");
		return PTR_ERR(gpmc_l3_clk);
	}

	if (!clk_get_rate(gpmc_l3_clk)) {
		dev_err(&pdev->dev, "Invalid GPMC fck clock rate\n");
		return -EINVAL;
	}

	if (pdev->dev.of_node) {
		rc = gpmc_probe_dt(pdev);
		if (rc)
			return rc;
	} else {
		gpmc_cs_num = GPMC_CS_NUM;
		gpmc_nr_waitpins = GPMC_NR_WAITPINS;
	}

	pm_runtime_enable(&pdev->dev);
	pm_runtime_get_sync(&pdev->dev);

	l = gpmc_read_reg(GPMC_REVISION);

	/*
	 * FIXME: Once device-tree migration is complete the below flags
	 * should be populated based upon the device-tree compatible
	 * string. For now just use the IP revision. OMAP3+ devices have
	 * the wr_access and wr_data_mux_bus register fields. OMAP4+
	 * devices support the addr-addr-data multiplex protocol.
	 *
	 * GPMC IP revisions:
	 * - OMAP24xx			= 2.0
	 * - OMAP3xxx			= 5.0
	 * - OMAP44xx/54xx/AM335x	= 6.0
	 */
	if (GPMC_REVISION_MAJOR(l) > 0x4)
		gpmc_capability = GPMC_HAS_WR_ACCESS | GPMC_HAS_WR_DATA_MUX_BUS;
	if (GPMC_REVISION_MAJOR(l) > 0x5)
		gpmc_capability |= GPMC_HAS_MUX_AAD;
	dev_info(gpmc->dev, "GPMC revision %d.%d\n", GPMC_REVISION_MAJOR(l),
		 GPMC_REVISION_MINOR(l));

	gpmc_mem_init();
	rc = gpmc_gpio_init(gpmc);
	if (rc)
		goto gpio_init_failed;

	gpmc->nirqs = GPMC_NR_NAND_IRQS + gpmc_nr_waitpins;
	rc = gpmc_setup_irq(gpmc);
	if (rc) {
		dev_err(gpmc->dev, "gpmc_setup_irq failed\n");
		goto gpio_init_failed;
	}

	gpmc_probe_dt_children(pdev);

	return 0;

gpio_init_failed:
	gpmc_mem_exit();
	pm_runtime_put_sync(&pdev->dev);
	pm_runtime_disable(&pdev->dev);

	return rc;
}