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
typedef  int u32 ;
struct hidma_tre {int dummy; } ;
struct hidma_lldev {int nr_tres; scalar_t__ evca; scalar_t__ tre_write_offset; int /*<<< orphan*/  pending_tre_count; int /*<<< orphan*/ * trepool; int /*<<< orphan*/  task; scalar_t__ initialized; } ;

/* Variables and functions */
 int ENODEV ; 
 scalar_t__ HIDMA_EVCA_IRQ_CLR_REG ; 
 scalar_t__ HIDMA_EVCA_IRQ_EN_REG ; 
 scalar_t__ HIDMA_EVCA_IRQ_STAT_REG ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int hidma_ll_reset (struct hidma_lldev*) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int readl (scalar_t__) ; 
 int /*<<< orphan*/  tasklet_kill (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

int hidma_ll_uninit(struct hidma_lldev *lldev)
{
	u32 required_bytes;
	int rc = 0;
	u32 val;

	if (!lldev)
		return -ENODEV;

	if (!lldev->initialized)
		return 0;

	lldev->initialized = 0;

	required_bytes = sizeof(struct hidma_tre) * lldev->nr_tres;
	tasklet_kill(&lldev->task);
	memset(lldev->trepool, 0, required_bytes);
	lldev->trepool = NULL;
	atomic_set(&lldev->pending_tre_count, 0);
	lldev->tre_write_offset = 0;

	rc = hidma_ll_reset(lldev);

	/*
	 * Clear all pending interrupts again.
	 * Otherwise, we observe reset complete interrupts.
	 */
	val = readl(lldev->evca + HIDMA_EVCA_IRQ_STAT_REG);
	writel(val, lldev->evca + HIDMA_EVCA_IRQ_CLR_REG);
	writel(0, lldev->evca + HIDMA_EVCA_IRQ_EN_REG);
	return rc;
}