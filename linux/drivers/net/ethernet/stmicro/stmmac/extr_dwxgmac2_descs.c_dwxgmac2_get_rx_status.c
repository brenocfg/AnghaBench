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
struct stmmac_extra_stats {int dummy; } ;
struct dma_desc {int /*<<< orphan*/  des3; } ;

/* Variables and functions */
 unsigned int XGMAC_RDES3_CTXT ; 
 unsigned int XGMAC_RDES3_ES ; 
 unsigned int XGMAC_RDES3_LD ; 
 unsigned int XGMAC_RDES3_OWN ; 
 int discard_frame ; 
 int dma_own ; 
 int good_frame ; 
 unsigned int le32_to_cpu (int /*<<< orphan*/ ) ; 
 scalar_t__ likely (int) ; 
 int rx_not_ls ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int dwxgmac2_get_rx_status(void *data, struct stmmac_extra_stats *x,
				  struct dma_desc *p)
{
	unsigned int rdes3 = le32_to_cpu(p->des3);

	if (unlikely(rdes3 & XGMAC_RDES3_OWN))
		return dma_own;
	if (unlikely(rdes3 & XGMAC_RDES3_CTXT))
		return discard_frame;
	if (likely(!(rdes3 & XGMAC_RDES3_LD)))
		return rx_not_ls;
	if (unlikely((rdes3 & XGMAC_RDES3_ES) && (rdes3 & XGMAC_RDES3_LD)))
		return discard_frame;

	return good_frame;
}