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
struct artpec6_crypto_req_common {int dummy; } ;
typedef  int /*<<< orphan*/  dma_addr_t ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_TO_DEVICE ; 
 int artpec6_crypto_dma_map_single (struct artpec6_crypto_req_common*,void*,unsigned int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int artpec6_crypto_setup_out_descr_phys (struct artpec6_crypto_req_common*,int /*<<< orphan*/ ,unsigned int,int) ; 
 int artpec6_crypto_setup_out_descr_short (struct artpec6_crypto_req_common*,void*,unsigned int,int) ; 

__attribute__((used)) static int
artpec6_crypto_setup_out_descr(struct artpec6_crypto_req_common *common,
			       void *dst, unsigned int len, bool eop,
			       bool use_short)
{
	if (use_short && len < 7) {
		return artpec6_crypto_setup_out_descr_short(common, dst, len,
							    eop);
	} else {
		int ret;
		dma_addr_t dma_addr;

		ret = artpec6_crypto_dma_map_single(common, dst, len,
						   DMA_TO_DEVICE,
						   &dma_addr);
		if (ret)
			return ret;

		return artpec6_crypto_setup_out_descr_phys(common, dma_addr,
							   len, eop);
	}
}