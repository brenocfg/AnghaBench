#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_3__ ;
typedef  struct TYPE_17__   TYPE_2__ ;
typedef  struct TYPE_16__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_16__ {int /*<<< orphan*/  of_node; } ;
struct spi_master {int auto_runtime_pm; int mode_bits; int num_chipselect; int /*<<< orphan*/ * cs_gpios; int /*<<< orphan*/  flags; int /*<<< orphan*/  setup; int /*<<< orphan*/  can_dma; int /*<<< orphan*/  transfer_one; int /*<<< orphan*/  prepare_message; int /*<<< orphan*/  set_cs; TYPE_1__ dev; } ;
struct resource {int dummy; } ;
struct TYPE_18__ {int /*<<< orphan*/  coherent_dma_mask; int /*<<< orphan*/ * dma_mask; int /*<<< orphan*/  of_node; } ;
struct platform_device {TYPE_3__ dev; } ;
struct of_device_id {TYPE_2__* data; } ;
struct mtk_spi {int pad_num; scalar_t__* pad_sel; TYPE_2__* dev_comp; void* spi_clk; void* parent_clk; void* sel_clk; void* base; } ;
struct TYPE_17__ {scalar_t__ dma_ext; scalar_t__ need_pad_sel; scalar_t__ must_tx; } ;

/* Variables and functions */
 int DMA_ADDR_DEF_BITS ; 
 int DMA_ADDR_EXT_BITS ; 
 int /*<<< orphan*/  DMA_BIT_MASK (int) ; 
 int EINVAL ; 
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 int /*<<< orphan*/  IRQF_TRIGGER_NONE ; 
 scalar_t__ IS_ERR (void*) ; 
 scalar_t__ MT8173_SPI_MAX_PAD_SEL ; 
 int PTR_ERR (void*) ; 
 int SPI_CPHA ; 
 int SPI_CPOL ; 
 int SPI_LSB_FIRST ; 
 int /*<<< orphan*/  SPI_MASTER_MUST_TX ; 
 int /*<<< orphan*/  clk_disable_unprepare (void*) ; 
 int clk_prepare_enable (void*) ; 
 int clk_set_parent (void*,void*) ; 
 int /*<<< orphan*/  dev_err (TYPE_3__*,char*,...) ; 
 int /*<<< orphan*/  dev_name (TYPE_3__*) ; 
 int /*<<< orphan*/  dev_notice (TYPE_3__*,char*,int,int) ; 
 void* devm_clk_get (TYPE_3__*,char*) ; 
 int devm_gpio_request (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 void* devm_ioremap_resource (TYPE_3__*,struct resource*) ; 
 scalar_t__* devm_kmalloc_array (TYPE_3__*,int,int,int /*<<< orphan*/ ) ; 
 int devm_request_irq (TYPE_3__*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct spi_master*) ; 
 int devm_spi_register_master (TYPE_3__*,struct spi_master*) ; 
 int dma_set_mask (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtk_spi_can_dma ; 
 int /*<<< orphan*/  mtk_spi_interrupt ; 
 int /*<<< orphan*/  mtk_spi_of_match ; 
 int /*<<< orphan*/  mtk_spi_prepare_message ; 
 int /*<<< orphan*/  mtk_spi_set_cs ; 
 int /*<<< orphan*/  mtk_spi_setup ; 
 int /*<<< orphan*/  mtk_spi_transfer_one ; 
 struct of_device_id* of_match_node (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int of_property_count_u32_elems (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  of_property_read_u32_index (int /*<<< orphan*/ ,char*,int,scalar_t__*) ; 
 int platform_get_irq (struct platform_device*,int /*<<< orphan*/ ) ; 
 struct resource* platform_get_resource (struct platform_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct spi_master*) ; 
 int /*<<< orphan*/  pm_runtime_disable (TYPE_3__*) ; 
 int /*<<< orphan*/  pm_runtime_enable (TYPE_3__*) ; 
 struct spi_master* spi_alloc_master (TYPE_3__*,int) ; 
 struct mtk_spi* spi_master_get_devdata (struct spi_master*) ; 
 int /*<<< orphan*/  spi_master_put (struct spi_master*) ; 

__attribute__((used)) static int mtk_spi_probe(struct platform_device *pdev)
{
	struct spi_master *master;
	struct mtk_spi *mdata;
	const struct of_device_id *of_id;
	struct resource *res;
	int i, irq, ret, addr_bits;

	master = spi_alloc_master(&pdev->dev, sizeof(*mdata));
	if (!master) {
		dev_err(&pdev->dev, "failed to alloc spi master\n");
		return -ENOMEM;
	}

	master->auto_runtime_pm = true;
	master->dev.of_node = pdev->dev.of_node;
	master->mode_bits = SPI_CPOL | SPI_CPHA | SPI_LSB_FIRST;

	master->set_cs = mtk_spi_set_cs;
	master->prepare_message = mtk_spi_prepare_message;
	master->transfer_one = mtk_spi_transfer_one;
	master->can_dma = mtk_spi_can_dma;
	master->setup = mtk_spi_setup;

	of_id = of_match_node(mtk_spi_of_match, pdev->dev.of_node);
	if (!of_id) {
		dev_err(&pdev->dev, "failed to probe of_node\n");
		ret = -EINVAL;
		goto err_put_master;
	}

	mdata = spi_master_get_devdata(master);
	mdata->dev_comp = of_id->data;
	if (mdata->dev_comp->must_tx)
		master->flags = SPI_MASTER_MUST_TX;

	if (mdata->dev_comp->need_pad_sel) {
		mdata->pad_num = of_property_count_u32_elems(
			pdev->dev.of_node,
			"mediatek,pad-select");
		if (mdata->pad_num < 0) {
			dev_err(&pdev->dev,
				"No 'mediatek,pad-select' property\n");
			ret = -EINVAL;
			goto err_put_master;
		}

		mdata->pad_sel = devm_kmalloc_array(&pdev->dev, mdata->pad_num,
						    sizeof(u32), GFP_KERNEL);
		if (!mdata->pad_sel) {
			ret = -ENOMEM;
			goto err_put_master;
		}

		for (i = 0; i < mdata->pad_num; i++) {
			of_property_read_u32_index(pdev->dev.of_node,
						   "mediatek,pad-select",
						   i, &mdata->pad_sel[i]);
			if (mdata->pad_sel[i] > MT8173_SPI_MAX_PAD_SEL) {
				dev_err(&pdev->dev, "wrong pad-sel[%d]: %u\n",
					i, mdata->pad_sel[i]);
				ret = -EINVAL;
				goto err_put_master;
			}
		}
	}

	platform_set_drvdata(pdev, master);

	res = platform_get_resource(pdev, IORESOURCE_MEM, 0);
	if (!res) {
		ret = -ENODEV;
		dev_err(&pdev->dev, "failed to determine base address\n");
		goto err_put_master;
	}

	mdata->base = devm_ioremap_resource(&pdev->dev, res);
	if (IS_ERR(mdata->base)) {
		ret = PTR_ERR(mdata->base);
		goto err_put_master;
	}

	irq = platform_get_irq(pdev, 0);
	if (irq < 0) {
		ret = irq;
		goto err_put_master;
	}

	if (!pdev->dev.dma_mask)
		pdev->dev.dma_mask = &pdev->dev.coherent_dma_mask;

	ret = devm_request_irq(&pdev->dev, irq, mtk_spi_interrupt,
			       IRQF_TRIGGER_NONE, dev_name(&pdev->dev), master);
	if (ret) {
		dev_err(&pdev->dev, "failed to register irq (%d)\n", ret);
		goto err_put_master;
	}

	mdata->parent_clk = devm_clk_get(&pdev->dev, "parent-clk");
	if (IS_ERR(mdata->parent_clk)) {
		ret = PTR_ERR(mdata->parent_clk);
		dev_err(&pdev->dev, "failed to get parent-clk: %d\n", ret);
		goto err_put_master;
	}

	mdata->sel_clk = devm_clk_get(&pdev->dev, "sel-clk");
	if (IS_ERR(mdata->sel_clk)) {
		ret = PTR_ERR(mdata->sel_clk);
		dev_err(&pdev->dev, "failed to get sel-clk: %d\n", ret);
		goto err_put_master;
	}

	mdata->spi_clk = devm_clk_get(&pdev->dev, "spi-clk");
	if (IS_ERR(mdata->spi_clk)) {
		ret = PTR_ERR(mdata->spi_clk);
		dev_err(&pdev->dev, "failed to get spi-clk: %d\n", ret);
		goto err_put_master;
	}

	ret = clk_prepare_enable(mdata->spi_clk);
	if (ret < 0) {
		dev_err(&pdev->dev, "failed to enable spi_clk (%d)\n", ret);
		goto err_put_master;
	}

	ret = clk_set_parent(mdata->sel_clk, mdata->parent_clk);
	if (ret < 0) {
		dev_err(&pdev->dev, "failed to clk_set_parent (%d)\n", ret);
		clk_disable_unprepare(mdata->spi_clk);
		goto err_put_master;
	}

	clk_disable_unprepare(mdata->spi_clk);

	pm_runtime_enable(&pdev->dev);

	ret = devm_spi_register_master(&pdev->dev, master);
	if (ret) {
		dev_err(&pdev->dev, "failed to register master (%d)\n", ret);
		goto err_disable_runtime_pm;
	}

	if (mdata->dev_comp->need_pad_sel) {
		if (mdata->pad_num != master->num_chipselect) {
			dev_err(&pdev->dev,
				"pad_num does not match num_chipselect(%d != %d)\n",
				mdata->pad_num, master->num_chipselect);
			ret = -EINVAL;
			goto err_disable_runtime_pm;
		}

		if (!master->cs_gpios && master->num_chipselect > 1) {
			dev_err(&pdev->dev,
				"cs_gpios not specified and num_chipselect > 1\n");
			ret = -EINVAL;
			goto err_disable_runtime_pm;
		}

		if (master->cs_gpios) {
			for (i = 0; i < master->num_chipselect; i++) {
				ret = devm_gpio_request(&pdev->dev,
							master->cs_gpios[i],
							dev_name(&pdev->dev));
				if (ret) {
					dev_err(&pdev->dev,
						"can't get CS GPIO %i\n", i);
					goto err_disable_runtime_pm;
				}
			}
		}
	}

	if (mdata->dev_comp->dma_ext)
		addr_bits = DMA_ADDR_EXT_BITS;
	else
		addr_bits = DMA_ADDR_DEF_BITS;
	ret = dma_set_mask(&pdev->dev, DMA_BIT_MASK(addr_bits));
	if (ret)
		dev_notice(&pdev->dev, "SPI dma_set_mask(%d) failed, ret:%d\n",
			   addr_bits, ret);

	return 0;

err_disable_runtime_pm:
	pm_runtime_disable(&pdev->dev);
err_put_master:
	spi_master_put(master);

	return ret;
}