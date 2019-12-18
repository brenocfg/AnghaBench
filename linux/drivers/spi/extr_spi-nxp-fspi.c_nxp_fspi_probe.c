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
struct TYPE_2__ {struct device_node* of_node; } ;
struct spi_controller {int mode_bits; int bus_num; TYPE_1__ dev; int /*<<< orphan*/ * mem_ops; int /*<<< orphan*/  num_chipselect; } ;
struct resource {int /*<<< orphan*/  start; } ;
struct device {struct device_node* of_node; } ;
struct platform_device {int /*<<< orphan*/  name; struct device dev; } ;
struct nxp_fspi {int /*<<< orphan*/  lock; void* clk; void* clk_en; int /*<<< orphan*/  memmap_phy_size; int /*<<< orphan*/  memmap_phy; void* ahb_addr; void* iobase; int /*<<< orphan*/  devtype_data; struct device* dev; } ;
struct device_node {int dummy; } ;

/* Variables and functions */
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 scalar_t__ IS_ERR (void*) ; 
 int /*<<< orphan*/  NXP_FSPI_MAX_CHIPSELECT ; 
 int PTR_ERR (void*) ; 
 int SPI_RX_DUAL ; 
 int SPI_RX_OCTAL ; 
 int SPI_RX_QUAD ; 
 int SPI_TX_DUAL ; 
 int SPI_TX_OCTAL ; 
 int SPI_TX_QUAD ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,...) ; 
 void* devm_clk_get (struct device*,char*) ; 
 void* devm_ioremap_resource (struct device*,struct resource*) ; 
 int devm_request_irq (struct device*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct nxp_fspi*) ; 
 int /*<<< orphan*/  mutex_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nxp_fspi_clk_disable_unprep (struct nxp_fspi*) ; 
 int nxp_fspi_clk_prep_enable (struct nxp_fspi*) ; 
 int /*<<< orphan*/  nxp_fspi_default_setup (struct nxp_fspi*) ; 
 int /*<<< orphan*/  nxp_fspi_irq_handler ; 
 int /*<<< orphan*/  nxp_fspi_mem_ops ; 
 int /*<<< orphan*/  of_device_get_match_data (struct device*) ; 
 int platform_get_irq (struct platform_device*,int /*<<< orphan*/ ) ; 
 struct resource* platform_get_resource_byname (struct platform_device*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct nxp_fspi*) ; 
 int /*<<< orphan*/  resource_size (struct resource*) ; 
 struct spi_controller* spi_alloc_master (struct device*,int) ; 
 struct nxp_fspi* spi_controller_get_devdata (struct spi_controller*) ; 
 int /*<<< orphan*/  spi_controller_put (struct spi_controller*) ; 
 int spi_register_controller (struct spi_controller*) ; 

__attribute__((used)) static int nxp_fspi_probe(struct platform_device *pdev)
{
	struct spi_controller *ctlr;
	struct device *dev = &pdev->dev;
	struct device_node *np = dev->of_node;
	struct resource *res;
	struct nxp_fspi *f;
	int ret;

	ctlr = spi_alloc_master(&pdev->dev, sizeof(*f));
	if (!ctlr)
		return -ENOMEM;

	ctlr->mode_bits = SPI_RX_DUAL | SPI_RX_QUAD | SPI_RX_OCTAL |
			  SPI_TX_DUAL | SPI_TX_QUAD | SPI_TX_OCTAL;

	f = spi_controller_get_devdata(ctlr);
	f->dev = dev;
	f->devtype_data = of_device_get_match_data(dev);
	if (!f->devtype_data) {
		ret = -ENODEV;
		goto err_put_ctrl;
	}

	platform_set_drvdata(pdev, f);

	/* find the resources - configuration register address space */
	res = platform_get_resource_byname(pdev, IORESOURCE_MEM, "fspi_base");
	f->iobase = devm_ioremap_resource(dev, res);
	if (IS_ERR(f->iobase)) {
		ret = PTR_ERR(f->iobase);
		goto err_put_ctrl;
	}

	/* find the resources - controller memory mapped space */
	res = platform_get_resource_byname(pdev, IORESOURCE_MEM, "fspi_mmap");
	f->ahb_addr = devm_ioremap_resource(dev, res);
	if (IS_ERR(f->ahb_addr)) {
		ret = PTR_ERR(f->ahb_addr);
		goto err_put_ctrl;
	}

	/* assign memory mapped starting address and mapped size. */
	f->memmap_phy = res->start;
	f->memmap_phy_size = resource_size(res);

	/* find the clocks */
	f->clk_en = devm_clk_get(dev, "fspi_en");
	if (IS_ERR(f->clk_en)) {
		ret = PTR_ERR(f->clk_en);
		goto err_put_ctrl;
	}

	f->clk = devm_clk_get(dev, "fspi");
	if (IS_ERR(f->clk)) {
		ret = PTR_ERR(f->clk);
		goto err_put_ctrl;
	}

	ret = nxp_fspi_clk_prep_enable(f);
	if (ret) {
		dev_err(dev, "can not enable the clock\n");
		goto err_put_ctrl;
	}

	/* find the irq */
	ret = platform_get_irq(pdev, 0);
	if (ret < 0)
		goto err_disable_clk;

	ret = devm_request_irq(dev, ret,
			nxp_fspi_irq_handler, 0, pdev->name, f);
	if (ret) {
		dev_err(dev, "failed to request irq: %d\n", ret);
		goto err_disable_clk;
	}

	mutex_init(&f->lock);

	ctlr->bus_num = -1;
	ctlr->num_chipselect = NXP_FSPI_MAX_CHIPSELECT;
	ctlr->mem_ops = &nxp_fspi_mem_ops;

	nxp_fspi_default_setup(f);

	ctlr->dev.of_node = np;

	ret = spi_register_controller(ctlr);
	if (ret)
		goto err_destroy_mutex;

	return 0;

err_destroy_mutex:
	mutex_destroy(&f->lock);

err_disable_clk:
	nxp_fspi_clk_disable_unprep(f);

err_put_ctrl:
	spi_controller_put(ctlr);

	dev_err(dev, "NXP FSPI probe failed\n");
	return ret;
}