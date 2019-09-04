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
struct sh_mobile_i2c_data {void* dma_rx; void* dma_tx; } ;

/* Variables and functions */
 int /*<<< orphan*/  EPROBE_DEFER ; 
 void* ERR_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IS_ERR (void*) ; 
 int /*<<< orphan*/  dma_release_channel (void*) ; 

__attribute__((used)) static void sh_mobile_i2c_release_dma(struct sh_mobile_i2c_data *pd)
{
	if (!IS_ERR(pd->dma_tx)) {
		dma_release_channel(pd->dma_tx);
		pd->dma_tx = ERR_PTR(-EPROBE_DEFER);
	}

	if (!IS_ERR(pd->dma_rx)) {
		dma_release_channel(pd->dma_rx);
		pd->dma_rx = ERR_PTR(-EPROBE_DEFER);
	}
}