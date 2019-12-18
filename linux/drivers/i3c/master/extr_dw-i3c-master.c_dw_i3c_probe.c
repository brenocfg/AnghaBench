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
struct resource {int dummy; } ;
struct platform_device {int /*<<< orphan*/  dev; } ;
struct TYPE_4__ {int /*<<< orphan*/  datafifodepth; int /*<<< orphan*/  cmdfifodepth; } ;
struct TYPE_3__ {int /*<<< orphan*/  list; int /*<<< orphan*/  lock; } ;
struct dw_i3c_master {int datstartaddr; int maxdevs; scalar_t__ core_clk; scalar_t__ core_rst; int /*<<< orphan*/  base; int /*<<< orphan*/  free_pos; scalar_t__ regs; TYPE_2__ caps; TYPE_1__ xferqueue; } ;

/* Variables and functions */
 scalar_t__ DATA_BUFFER_STATUS_LEVEL ; 
 int /*<<< orphan*/  DATA_BUFFER_STATUS_LEVEL_TX (int) ; 
 scalar_t__ DEVICE_ADDR_TABLE_POINTER ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GENMASK (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  INTR_ALL ; 
 scalar_t__ INTR_STATUS ; 
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 scalar_t__ IS_ERR (scalar_t__) ; 
 int PTR_ERR (scalar_t__) ; 
 scalar_t__ QUEUE_STATUS_LEVEL ; 
 int /*<<< orphan*/  QUEUE_STATUS_LEVEL_CMD (int) ; 
 int /*<<< orphan*/  clk_disable_unprepare (scalar_t__) ; 
 int clk_prepare_enable (scalar_t__) ; 
 int /*<<< orphan*/  dev_name (int /*<<< orphan*/ *) ; 
 scalar_t__ devm_clk_get (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ devm_ioremap_resource (int /*<<< orphan*/ *,struct resource*) ; 
 struct dw_i3c_master* devm_kzalloc (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int devm_request_irq (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct dw_i3c_master*) ; 
 scalar_t__ devm_reset_control_get_optional_exclusive (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  dw_i3c_master_irq_handler ; 
 int /*<<< orphan*/  dw_mipi_i3c_ops ; 
 int i3c_master_register (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int platform_get_irq (struct platform_device*,int /*<<< orphan*/ ) ; 
 struct resource* platform_get_resource (struct platform_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct dw_i3c_master*) ; 
 int readl (scalar_t__) ; 
 int /*<<< orphan*/  reset_control_assert (scalar_t__) ; 
 int /*<<< orphan*/  reset_control_deassert (scalar_t__) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static int dw_i3c_probe(struct platform_device *pdev)
{
	struct dw_i3c_master *master;
	struct resource *res;
	int ret, irq;

	master = devm_kzalloc(&pdev->dev, sizeof(*master), GFP_KERNEL);
	if (!master)
		return -ENOMEM;

	res = platform_get_resource(pdev, IORESOURCE_MEM, 0);
	master->regs = devm_ioremap_resource(&pdev->dev, res);
	if (IS_ERR(master->regs))
		return PTR_ERR(master->regs);

	master->core_clk = devm_clk_get(&pdev->dev, NULL);
	if (IS_ERR(master->core_clk))
		return PTR_ERR(master->core_clk);

	master->core_rst = devm_reset_control_get_optional_exclusive(&pdev->dev,
								    "core_rst");
	if (IS_ERR(master->core_rst))
		return PTR_ERR(master->core_rst);

	ret = clk_prepare_enable(master->core_clk);
	if (ret)
		goto err_disable_core_clk;

	reset_control_deassert(master->core_rst);

	spin_lock_init(&master->xferqueue.lock);
	INIT_LIST_HEAD(&master->xferqueue.list);

	writel(INTR_ALL, master->regs + INTR_STATUS);
	irq = platform_get_irq(pdev, 0);
	ret = devm_request_irq(&pdev->dev, irq,
			       dw_i3c_master_irq_handler, 0,
			       dev_name(&pdev->dev), master);
	if (ret)
		goto err_assert_rst;

	platform_set_drvdata(pdev, master);

	/* Information regarding the FIFOs/QUEUEs depth */
	ret = readl(master->regs + QUEUE_STATUS_LEVEL);
	master->caps.cmdfifodepth = QUEUE_STATUS_LEVEL_CMD(ret);

	ret = readl(master->regs + DATA_BUFFER_STATUS_LEVEL);
	master->caps.datafifodepth = DATA_BUFFER_STATUS_LEVEL_TX(ret);

	ret = readl(master->regs + DEVICE_ADDR_TABLE_POINTER);
	master->datstartaddr = ret;
	master->maxdevs = ret >> 16;
	master->free_pos = GENMASK(master->maxdevs - 1, 0);

	ret = i3c_master_register(&master->base, &pdev->dev,
				  &dw_mipi_i3c_ops, false);
	if (ret)
		goto err_assert_rst;

	return 0;

err_assert_rst:
	reset_control_assert(master->core_rst);

err_disable_core_clk:
	clk_disable_unprepare(master->core_clk);

	return ret;
}