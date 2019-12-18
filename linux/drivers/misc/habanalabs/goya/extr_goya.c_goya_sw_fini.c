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
struct hl_device {int /*<<< orphan*/  dma_pool; int /*<<< orphan*/  cpu_accessible_dma_address; int /*<<< orphan*/  cpu_accessible_dma_mem; TYPE_1__* asic_funcs; int /*<<< orphan*/  cpu_accessible_dma_pool; struct goya_device* asic_specific; } ;
struct goya_device {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* asic_dma_free_coherent ) (struct hl_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  HL_CPU_ACCESSIBLE_MEM_SIZE ; 
 int /*<<< orphan*/  dma_pool_destroy (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gen_pool_destroy (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct goya_device*) ; 
 int /*<<< orphan*/  stub1 (struct hl_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int goya_sw_fini(struct hl_device *hdev)
{
	struct goya_device *goya = hdev->asic_specific;

	gen_pool_destroy(hdev->cpu_accessible_dma_pool);

	hdev->asic_funcs->asic_dma_free_coherent(hdev,
			HL_CPU_ACCESSIBLE_MEM_SIZE,
			hdev->cpu_accessible_dma_mem,
			hdev->cpu_accessible_dma_address);

	dma_pool_destroy(hdev->dma_pool);

	kfree(goya);

	return 0;
}