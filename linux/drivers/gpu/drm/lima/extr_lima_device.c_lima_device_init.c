#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct resource {int dummy; } ;
struct lima_device {scalar_t__ id; int /*<<< orphan*/  empty_vm; int /*<<< orphan*/  dlbu_dma; scalar_t__ dlbu_cpu; int /*<<< orphan*/  dev; int /*<<< orphan*/  clk_gpu; int /*<<< orphan*/  clk_bus; int /*<<< orphan*/  iomem; int /*<<< orphan*/  pdev; int /*<<< orphan*/  va_end; scalar_t__ va_start; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_BIT_MASK (int) ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LIMA_PAGE_SIZE ; 
 int /*<<< orphan*/  LIMA_VA_RESERVE_END ; 
 int /*<<< orphan*/  LIMA_VA_RESERVE_START ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clk_get_rate (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  devm_ioremap_resource (int /*<<< orphan*/ ,struct resource*) ; 
 scalar_t__ dma_alloc_wc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_free_wc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_set_coherent_mask (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lima_clk_fini (struct lima_device*) ; 
 int lima_clk_init (struct lima_device*) ; 
 int /*<<< orphan*/  lima_fini_gp_pipe (struct lima_device*) ; 
 int /*<<< orphan*/  lima_fini_ip (struct lima_device*,int) ; 
 scalar_t__ lima_gpu_mali450 ; 
 int lima_init_gp_pipe (struct lima_device*) ; 
 int lima_init_ip (struct lima_device*,int) ; 
 int lima_init_pp_pipe (struct lima_device*) ; 
 int lima_ip_num ; 
 int /*<<< orphan*/  lima_regulator_fini (struct lima_device*) ; 
 int lima_regulator_init (struct lima_device*) ; 
 int /*<<< orphan*/  lima_vm_create (struct lima_device*) ; 
 int /*<<< orphan*/  lima_vm_put (int /*<<< orphan*/ ) ; 
 struct resource* platform_get_resource (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int lima_device_init(struct lima_device *ldev)
{
	int err, i;
	struct resource *res;

	dma_set_coherent_mask(ldev->dev, DMA_BIT_MASK(32));

	err = lima_clk_init(ldev);
	if (err)
		return err;

	err = lima_regulator_init(ldev);
	if (err)
		goto err_out0;

	ldev->empty_vm = lima_vm_create(ldev);
	if (!ldev->empty_vm) {
		err = -ENOMEM;
		goto err_out1;
	}

	ldev->va_start = 0;
	if (ldev->id == lima_gpu_mali450) {
		ldev->va_end = LIMA_VA_RESERVE_START;
		ldev->dlbu_cpu = dma_alloc_wc(
			ldev->dev, LIMA_PAGE_SIZE,
			&ldev->dlbu_dma, GFP_KERNEL);
		if (!ldev->dlbu_cpu) {
			err = -ENOMEM;
			goto err_out2;
		}
	} else
		ldev->va_end = LIMA_VA_RESERVE_END;

	res = platform_get_resource(ldev->pdev, IORESOURCE_MEM, 0);
	ldev->iomem = devm_ioremap_resource(ldev->dev, res);
	if (IS_ERR(ldev->iomem)) {
		dev_err(ldev->dev, "fail to ioremap iomem\n");
		err = PTR_ERR(ldev->iomem);
		goto err_out3;
	}

	for (i = 0; i < lima_ip_num; i++) {
		err = lima_init_ip(ldev, i);
		if (err)
			goto err_out4;
	}

	err = lima_init_gp_pipe(ldev);
	if (err)
		goto err_out4;

	err = lima_init_pp_pipe(ldev);
	if (err)
		goto err_out5;

	dev_info(ldev->dev, "bus rate = %lu\n", clk_get_rate(ldev->clk_bus));
	dev_info(ldev->dev, "mod rate = %lu", clk_get_rate(ldev->clk_gpu));

	return 0;

err_out5:
	lima_fini_gp_pipe(ldev);
err_out4:
	while (--i >= 0)
		lima_fini_ip(ldev, i);
err_out3:
	if (ldev->dlbu_cpu)
		dma_free_wc(ldev->dev, LIMA_PAGE_SIZE,
			    ldev->dlbu_cpu, ldev->dlbu_dma);
err_out2:
	lima_vm_put(ldev->empty_vm);
err_out1:
	lima_regulator_fini(ldev);
err_out0:
	lima_clk_fini(ldev);
	return err;
}