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
typedef  int /*<<< orphan*/  uint64_t ;
struct msm_dsi_host {int /*<<< orphan*/  tx_buf_paddr; } ;

/* Variables and functions */
 int EINVAL ; 

int dsi_dma_base_get_v2(struct msm_dsi_host *msm_host, uint64_t *dma_base)
{
	if (!dma_base)
		return -EINVAL;

	*dma_base = msm_host->tx_buf_paddr;
	return 0;
}