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
struct hl_device {int /*<<< orphan*/  dma_pool; int /*<<< orphan*/  cpu_accessible_dma_address; scalar_t__ cpu_accessible_dma_mem; TYPE_2__* asic_funcs; int /*<<< orphan*/  cpu_accessible_dma_pool; int /*<<< orphan*/  dev; TYPE_1__* pdev; struct goya_device* asic_specific; } ;
struct goya_device {int /*<<< orphan*/  hw_queues_lock; void* ic_clk; void* tpc_clk; void* mme_clk; int /*<<< orphan*/  ddr_bar_cur_addr; } ;
struct TYPE_4__ {int /*<<< orphan*/  (* asic_dma_free_coherent ) (struct hl_device*,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ;scalar_t__ (* asic_dma_alloc_coherent ) (struct hl_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ;} ;
struct TYPE_3__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRAM_PHYS_BASE ; 
 int EFAULT ; 
 int ENOMEM ; 
 int GFP_KERNEL ; 
 int /*<<< orphan*/  GOYA_DMA_POOL_BLK_SIZE ; 
 void* GOYA_PLL_FREQ_LOW ; 
 int /*<<< orphan*/  HL_CPU_ACCESSIBLE_MEM_SIZE ; 
 int __GFP_ZERO ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  dev_name (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_pool_create (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_pool_destroy (int /*<<< orphan*/ ) ; 
 int gen_pool_add (int /*<<< orphan*/ ,uintptr_t,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  gen_pool_create (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  gen_pool_destroy (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ilog2 (int) ; 
 int /*<<< orphan*/  kfree (struct goya_device*) ; 
 struct goya_device* kzalloc (int,int) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 scalar_t__ stub1 (struct hl_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  stub2 (struct hl_device*,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int goya_sw_init(struct hl_device *hdev)
{
	struct goya_device *goya;
	int rc;

	/* Allocate device structure */
	goya = kzalloc(sizeof(*goya), GFP_KERNEL);
	if (!goya)
		return -ENOMEM;

	/* according to goya_init_iatu */
	goya->ddr_bar_cur_addr = DRAM_PHYS_BASE;

	goya->mme_clk = GOYA_PLL_FREQ_LOW;
	goya->tpc_clk = GOYA_PLL_FREQ_LOW;
	goya->ic_clk = GOYA_PLL_FREQ_LOW;

	hdev->asic_specific = goya;

	/* Create DMA pool for small allocations */
	hdev->dma_pool = dma_pool_create(dev_name(hdev->dev),
			&hdev->pdev->dev, GOYA_DMA_POOL_BLK_SIZE, 8, 0);
	if (!hdev->dma_pool) {
		dev_err(hdev->dev, "failed to create DMA pool\n");
		rc = -ENOMEM;
		goto free_goya_device;
	}

	hdev->cpu_accessible_dma_mem =
			hdev->asic_funcs->asic_dma_alloc_coherent(hdev,
					HL_CPU_ACCESSIBLE_MEM_SIZE,
					&hdev->cpu_accessible_dma_address,
					GFP_KERNEL | __GFP_ZERO);

	if (!hdev->cpu_accessible_dma_mem) {
		rc = -ENOMEM;
		goto free_dma_pool;
	}

	dev_dbg(hdev->dev, "cpu accessible memory at bus address %pad\n",
		&hdev->cpu_accessible_dma_address);

	hdev->cpu_accessible_dma_pool = gen_pool_create(ilog2(32), -1);
	if (!hdev->cpu_accessible_dma_pool) {
		dev_err(hdev->dev,
			"Failed to create CPU accessible DMA pool\n");
		rc = -ENOMEM;
		goto free_cpu_dma_mem;
	}

	rc = gen_pool_add(hdev->cpu_accessible_dma_pool,
				(uintptr_t) hdev->cpu_accessible_dma_mem,
				HL_CPU_ACCESSIBLE_MEM_SIZE, -1);
	if (rc) {
		dev_err(hdev->dev,
			"Failed to add memory to CPU accessible DMA pool\n");
		rc = -EFAULT;
		goto free_cpu_accessible_dma_pool;
	}

	spin_lock_init(&goya->hw_queues_lock);

	return 0;

free_cpu_accessible_dma_pool:
	gen_pool_destroy(hdev->cpu_accessible_dma_pool);
free_cpu_dma_mem:
	hdev->asic_funcs->asic_dma_free_coherent(hdev,
			HL_CPU_ACCESSIBLE_MEM_SIZE,
			hdev->cpu_accessible_dma_mem,
			hdev->cpu_accessible_dma_address);
free_dma_pool:
	dma_pool_destroy(hdev->dma_pool);
free_goya_device:
	kfree(goya);

	return rc;
}