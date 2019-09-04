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
struct of_phandle_args {int args_count; int /*<<< orphan*/ * args; } ;
struct of_dma_filter_info {int /*<<< orphan*/  filter_fn; int /*<<< orphan*/  dma_cap; } ;
struct of_dma {struct of_dma_filter_info* of_dma_data; } ;
struct dma_chan {int dummy; } ;

/* Variables and functions */
 struct dma_chan* dma_request_channel (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static struct dma_chan *cppi41_dma_xlate(struct of_phandle_args *dma_spec,
		struct of_dma *ofdma)
{
	int count = dma_spec->args_count;
	struct of_dma_filter_info *info = ofdma->of_dma_data;

	if (!info || !info->filter_fn)
		return NULL;

	if (count != 2)
		return NULL;

	return dma_request_channel(info->dma_cap, info->filter_fn,
			&dma_spec->args[0]);
}