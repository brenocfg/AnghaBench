#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct resource {int /*<<< orphan*/  start; } ;
struct platform_device {int /*<<< orphan*/  dev; int /*<<< orphan*/  name; } ;
struct jz4740_adc {int irq; TYPE_3__* mem; scalar_t__ base; int /*<<< orphan*/  clk; struct irq_chip_generic* gc; int /*<<< orphan*/  clk_ref; int /*<<< orphan*/  lock; } ;
struct TYPE_6__ {int /*<<< orphan*/  irq_ack; int /*<<< orphan*/  irq_unmask; int /*<<< orphan*/  irq_mask; } ;
struct TYPE_5__ {int /*<<< orphan*/  ack; scalar_t__ mask; } ;
struct irq_chip_type {TYPE_2__ chip; TYPE_1__ regs; } ;
struct irq_chip_generic {struct irq_chip_type* chip_types; } ;
struct TYPE_7__ {int /*<<< orphan*/  start; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int EBUSY ; 
 int ENOENT ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 int /*<<< orphan*/  IRQ_GC_INIT_MASK_CACHE ; 
 int IRQ_LEVEL ; 
 int /*<<< orphan*/  IRQ_MSK (int) ; 
 int IRQ_NOPROBE ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 scalar_t__ JZ_REG_ADC_CTRL ; 
 scalar_t__ JZ_REG_ADC_ENABLE ; 
 int /*<<< orphan*/  JZ_REG_ADC_STATUS ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clk_get (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  clk_put (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,...) ; 
 struct jz4740_adc* devm_kzalloc (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  handle_level_irq ; 
 scalar_t__ ioremap_nocache (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iounmap (scalar_t__) ; 
 struct irq_chip_generic* irq_alloc_generic_chip (char*,int,int,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  irq_gc_ack_set_bit ; 
 int /*<<< orphan*/  irq_gc_mask_clr_bit ; 
 int /*<<< orphan*/  irq_gc_mask_set_bit ; 
 int /*<<< orphan*/  irq_set_chained_handler_and_data (int,int /*<<< orphan*/ ,struct irq_chip_generic*) ; 
 int /*<<< orphan*/  irq_setup_generic_chip (struct irq_chip_generic*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  jz4740_adc_cells ; 
 int /*<<< orphan*/  jz4740_adc_irq_demux ; 
 int mfd_add_devices (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct resource*,int,int /*<<< orphan*/ *) ; 
 void* platform_get_irq (struct platform_device*,int) ; 
 struct resource* platform_get_resource (struct platform_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct jz4740_adc*) ; 
 int /*<<< orphan*/  release_mem_region (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_3__* request_mem_region (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  resource_size (TYPE_3__*) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  writeb (int,scalar_t__) ; 

__attribute__((used)) static int jz4740_adc_probe(struct platform_device *pdev)
{
	struct irq_chip_generic *gc;
	struct irq_chip_type *ct;
	struct jz4740_adc *adc;
	struct resource *mem_base;
	int ret;
	int irq_base;

	adc = devm_kzalloc(&pdev->dev, sizeof(*adc), GFP_KERNEL);
	if (!adc)
		return -ENOMEM;

	adc->irq = platform_get_irq(pdev, 0);
	if (adc->irq < 0) {
		ret = adc->irq;
		dev_err(&pdev->dev, "Failed to get platform irq: %d\n", ret);
		return ret;
	}

	irq_base = platform_get_irq(pdev, 1);
	if (irq_base < 0) {
		dev_err(&pdev->dev, "Failed to get irq base: %d\n", irq_base);
		return irq_base;
	}

	mem_base = platform_get_resource(pdev, IORESOURCE_MEM, 0);
	if (!mem_base) {
		dev_err(&pdev->dev, "Failed to get platform mmio resource\n");
		return -ENOENT;
	}

	/* Only request the shared registers for the MFD driver */
	adc->mem = request_mem_region(mem_base->start, JZ_REG_ADC_STATUS,
					pdev->name);
	if (!adc->mem) {
		dev_err(&pdev->dev, "Failed to request mmio memory region\n");
		return -EBUSY;
	}

	adc->base = ioremap_nocache(adc->mem->start, resource_size(adc->mem));
	if (!adc->base) {
		ret = -EBUSY;
		dev_err(&pdev->dev, "Failed to ioremap mmio memory\n");
		goto err_release_mem_region;
	}

	adc->clk = clk_get(&pdev->dev, "adc");
	if (IS_ERR(adc->clk)) {
		ret = PTR_ERR(adc->clk);
		dev_err(&pdev->dev, "Failed to get clock: %d\n", ret);
		goto err_iounmap;
	}

	spin_lock_init(&adc->lock);
	atomic_set(&adc->clk_ref, 0);

	platform_set_drvdata(pdev, adc);

	gc = irq_alloc_generic_chip("INTC", 1, irq_base, adc->base,
		handle_level_irq);

	ct = gc->chip_types;
	ct->regs.mask = JZ_REG_ADC_CTRL;
	ct->regs.ack = JZ_REG_ADC_STATUS;
	ct->chip.irq_mask = irq_gc_mask_set_bit;
	ct->chip.irq_unmask = irq_gc_mask_clr_bit;
	ct->chip.irq_ack = irq_gc_ack_set_bit;

	irq_setup_generic_chip(gc, IRQ_MSK(5), IRQ_GC_INIT_MASK_CACHE, 0,
				IRQ_NOPROBE | IRQ_LEVEL);

	adc->gc = gc;

	irq_set_chained_handler_and_data(adc->irq, jz4740_adc_irq_demux, gc);

	writeb(0x00, adc->base + JZ_REG_ADC_ENABLE);
	writeb(0xff, adc->base + JZ_REG_ADC_CTRL);

	ret = mfd_add_devices(&pdev->dev, 0, jz4740_adc_cells,
			      ARRAY_SIZE(jz4740_adc_cells), mem_base,
			      irq_base, NULL);
	if (ret < 0)
		goto err_clk_put;

	return 0;

err_clk_put:
	clk_put(adc->clk);
err_iounmap:
	iounmap(adc->base);
err_release_mem_region:
	release_mem_region(adc->mem->start, resource_size(adc->mem));
	return ret;
}