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
struct dma_desc {int /*<<< orphan*/  des2; } ;

/* Variables and functions */
 int /*<<< orphan*/  XGMAC_TDES2_IOC ; 
 int /*<<< orphan*/  cpu_to_le32 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void dwxgmac2_set_tx_ic(struct dma_desc *p)
{
	p->des2 |= cpu_to_le32(XGMAC_TDES2_IOC);
}