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
struct of_phandle_args {int args_count; int /*<<< orphan*/ * args; } ;
struct of_dma {struct imxdma_engine* of_dma_data; } ;
struct imxdma_filter_data {int /*<<< orphan*/  request; struct imxdma_engine* imxdma; } ;
struct TYPE_2__ {int /*<<< orphan*/  cap_mask; } ;
struct imxdma_engine {TYPE_1__ dma_device; } ;
struct dma_chan {int dummy; } ;

/* Variables and functions */
 struct dma_chan* dma_request_channel (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct imxdma_filter_data*) ; 
 int /*<<< orphan*/  imxdma_filter_fn ; 

__attribute__((used)) static struct dma_chan *imxdma_xlate(struct of_phandle_args *dma_spec,
						struct of_dma *ofdma)
{
	int count = dma_spec->args_count;
	struct imxdma_engine *imxdma = ofdma->of_dma_data;
	struct imxdma_filter_data fdata = {
		.imxdma = imxdma,
	};

	if (count != 1)
		return NULL;

	fdata.request = dma_spec->args[0];

	return dma_request_channel(imxdma->dma_device.cap_mask,
					imxdma_filter_fn, &fdata);
}