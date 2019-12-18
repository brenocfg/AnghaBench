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
struct dma_desc {void* des3; void* des2; scalar_t__ des1; scalar_t__ des0; } ;

/* Variables and functions */
 unsigned int XGMAC_TDES3_CTXT ; 
 unsigned int XGMAC_TDES3_TCMSSV ; 
 void* cpu_to_le32 (unsigned int) ; 

__attribute__((used)) static void dwxgmac2_set_mss(struct dma_desc *p, unsigned int mss)
{
	p->des0 = 0;
	p->des1 = 0;
	p->des2 = cpu_to_le32(mss);
	p->des3 = cpu_to_le32(XGMAC_TDES3_CTXT | XGMAC_TDES3_TCMSSV);
}