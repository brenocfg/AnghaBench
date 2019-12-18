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
struct platform_device {int dummy; } ;
struct pdc_state {int /*<<< orphan*/  ring_pool; int /*<<< orphan*/  rx_buf_pool; int /*<<< orphan*/  rx_tasklet; } ;

/* Variables and functions */
 int /*<<< orphan*/  dma_pool_destroy (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pdc_free_debugfs () ; 
 int /*<<< orphan*/  pdc_hw_disable (struct pdc_state*) ; 
 struct pdc_state* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  tasklet_kill (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int pdc_remove(struct platform_device *pdev)
{
	struct pdc_state *pdcs = platform_get_drvdata(pdev);

	pdc_free_debugfs();

	tasklet_kill(&pdcs->rx_tasklet);

	pdc_hw_disable(pdcs);

	dma_pool_destroy(pdcs->rx_buf_pool);
	dma_pool_destroy(pdcs->ring_pool);
	return 0;
}