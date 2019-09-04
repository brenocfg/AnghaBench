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
struct device {int dummy; } ;
struct ahash_req_ctx {int /*<<< orphan*/  digest_result_dma_addr; int /*<<< orphan*/  digest_result_buff; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_BIDIRECTIONAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  dev_dbg (struct device*,char*,unsigned int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,unsigned int) ; 
 int /*<<< orphan*/  dma_map_single (struct device*,int /*<<< orphan*/ ,unsigned int,int /*<<< orphan*/ ) ; 
 scalar_t__ dma_mapping_error (struct device*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int cc_map_result(struct device *dev, struct ahash_req_ctx *state,
			 unsigned int digestsize)
{
	state->digest_result_dma_addr =
		dma_map_single(dev, state->digest_result_buff,
			       digestsize, DMA_BIDIRECTIONAL);
	if (dma_mapping_error(dev, state->digest_result_dma_addr)) {
		dev_err(dev, "Mapping digest result buffer %u B for DMA failed\n",
			digestsize);
		return -ENOMEM;
	}
	dev_dbg(dev, "Mapped digest result buffer %u B at va=%pK to dma=%pad\n",
		digestsize, state->digest_result_buff,
		&state->digest_result_dma_addr);

	return 0;
}