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
struct dma_desc {int /*<<< orphan*/  des2; int /*<<< orphan*/  des3; } ;

/* Variables and functions */
 int XGMAC_RDES2_HL ; 
 int XGMAC_RDES3_L34T ; 
 int le32_to_cpu (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int dwxgmac2_get_rx_header_len(struct dma_desc *p, unsigned int *len)
{
	if (le32_to_cpu(p->des3) & XGMAC_RDES3_L34T)
		*len = le32_to_cpu(p->des2) & XGMAC_RDES2_HL;
	return 0;
}