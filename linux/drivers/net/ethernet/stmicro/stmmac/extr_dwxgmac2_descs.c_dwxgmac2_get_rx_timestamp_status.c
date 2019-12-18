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
typedef  int /*<<< orphan*/  u32 ;
struct dma_desc {int /*<<< orphan*/  des3; } ;

/* Variables and functions */
 int EBUSY ; 
 unsigned int XGMAC_RDES3_CDA ; 
 int dwxgmac2_rx_check_timestamp (void*) ; 
 unsigned int le32_to_cpu (int /*<<< orphan*/ ) ; 
 scalar_t__ likely (unsigned int) ; 

__attribute__((used)) static int dwxgmac2_get_rx_timestamp_status(void *desc, void *next_desc,
					    u32 ats)
{
	struct dma_desc *p = (struct dma_desc *)desc;
	unsigned int rdes3 = le32_to_cpu(p->des3);
	int ret = -EBUSY;

	if (likely(rdes3 & XGMAC_RDES3_CDA))
		ret = dwxgmac2_rx_check_timestamp(next_desc);

	return !ret;
}