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
struct bcma_drv_pcie2 {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BCMA_CORE_PCIE2_CLK_CONTROL ; 
 int /*<<< orphan*/  PCIE2_CLKC_DISSPROMLD ; 
 int /*<<< orphan*/  PCIE2_CLKC_DLYPERST ; 
 int /*<<< orphan*/  pcie2_read32 (struct bcma_drv_pcie2*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pcie2_write32 (struct bcma_drv_pcie2*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static u32 bcma_core_pcie2_war_delay_perst_enab(struct bcma_drv_pcie2 *pcie2,
						bool enable)
{
	u32 val;

	/* restore back to default */
	val = pcie2_read32(pcie2, BCMA_CORE_PCIE2_CLK_CONTROL);
	val |= PCIE2_CLKC_DLYPERST;
	val &= ~PCIE2_CLKC_DISSPROMLD;
	if (enable) {
		val &= ~PCIE2_CLKC_DLYPERST;
		val |= PCIE2_CLKC_DISSPROMLD;
	}
	pcie2_write32(pcie2, (BCMA_CORE_PCIE2_CLK_CONTROL), val);
	/* flush */
	return pcie2_read32(pcie2, BCMA_CORE_PCIE2_CLK_CONTROL);
}