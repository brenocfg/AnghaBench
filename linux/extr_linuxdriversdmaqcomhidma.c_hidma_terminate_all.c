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
struct TYPE_4__ {int /*<<< orphan*/  dev; } ;
struct hidma_dev {TYPE_2__ ddev; int /*<<< orphan*/  lldev; } ;
struct TYPE_3__ {int /*<<< orphan*/  device; } ;
struct hidma_chan {TYPE_1__ chan; } ;
struct dma_chan {int dummy; } ;

/* Variables and functions */
 int hidma_ll_setup (int /*<<< orphan*/ ) ; 
 int hidma_terminate_channel (struct dma_chan*) ; 
 int /*<<< orphan*/  pm_runtime_get_sync (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm_runtime_mark_last_busy (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm_runtime_put_autosuspend (int /*<<< orphan*/ ) ; 
 struct hidma_chan* to_hidma_chan (struct dma_chan*) ; 
 struct hidma_dev* to_hidma_dev (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int hidma_terminate_all(struct dma_chan *chan)
{
	struct hidma_chan *mchan = to_hidma_chan(chan);
	struct hidma_dev *dmadev = to_hidma_dev(mchan->chan.device);
	int rc;

	rc = hidma_terminate_channel(chan);
	if (rc)
		return rc;

	/* reinitialize the hardware */
	pm_runtime_get_sync(dmadev->ddev.dev);
	rc = hidma_ll_setup(dmadev->lldev);
	pm_runtime_mark_last_busy(dmadev->ddev.dev);
	pm_runtime_put_autosuspend(dmadev->ddev.dev);
	return rc;
}