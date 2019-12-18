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
typedef  int u32 ;
struct dma_desc {int /*<<< orphan*/  des3; } ;

/* Variables and functions */
 int XGMAC_TDES3_SAIC ; 
 int XGMAC_TDES3_SAIC_SHIFT ; 
 int /*<<< orphan*/  cpu_to_le32 (int) ; 

__attribute__((used)) static void dwxgmac2_set_sarc(struct dma_desc *p, u32 sarc_type)
{
	sarc_type <<= XGMAC_TDES3_SAIC_SHIFT;

	p->des3 |= cpu_to_le32(sarc_type & XGMAC_TDES3_SAIC);
}