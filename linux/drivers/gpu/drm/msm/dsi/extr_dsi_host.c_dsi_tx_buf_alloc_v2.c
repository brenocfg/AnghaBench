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
struct msm_dsi_host {int tx_size; int /*<<< orphan*/  tx_buf; int /*<<< orphan*/  tx_buf_paddr; struct drm_device* dev; } ;
struct drm_device {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  dma_alloc_coherent (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

int dsi_tx_buf_alloc_v2(struct msm_dsi_host *msm_host, int size)
{
	struct drm_device *dev = msm_host->dev;

	msm_host->tx_buf = dma_alloc_coherent(dev->dev, size,
					&msm_host->tx_buf_paddr, GFP_KERNEL);
	if (!msm_host->tx_buf)
		return -ENOMEM;

	msm_host->tx_size = size;

	return 0;
}