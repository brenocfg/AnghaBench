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
typedef  int /*<<< orphan*/  u8 ;
struct device {int dummy; } ;
struct ahash_req_ctx {scalar_t__ digest_result_dma_addr; int /*<<< orphan*/  digest_result_buff; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_BIDIRECTIONAL ; 
 int /*<<< orphan*/  dev_dbg (struct device*,char*,int /*<<< orphan*/ ,scalar_t__*,unsigned int) ; 
 int /*<<< orphan*/  dma_unmap_single (struct device*,scalar_t__,unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ ,unsigned int) ; 

__attribute__((used)) static void cc_unmap_result(struct device *dev, struct ahash_req_ctx *state,
			    unsigned int digestsize, u8 *result)
{
	if (state->digest_result_dma_addr) {
		dma_unmap_single(dev, state->digest_result_dma_addr, digestsize,
				 DMA_BIDIRECTIONAL);
		dev_dbg(dev, "unmpa digest result buffer va (%pK) pa (%pad) len %u\n",
			state->digest_result_buff,
			&state->digest_result_dma_addr, digestsize);
		memcpy(result, state->digest_result_buff, digestsize);
	}
	state->digest_result_dma_addr = 0;
}