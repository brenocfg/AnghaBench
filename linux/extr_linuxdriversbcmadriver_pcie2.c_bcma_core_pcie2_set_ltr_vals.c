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
struct bcma_drv_pcie2 {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BCMA_CORE_PCIE2_CONFIGINDADDR ; 
 int /*<<< orphan*/  BCMA_CORE_PCIE2_CONFIGINDDATA ; 
 int /*<<< orphan*/  pcie2_write32 (struct bcma_drv_pcie2*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void bcma_core_pcie2_set_ltr_vals(struct bcma_drv_pcie2 *pcie2)
{
	/* LTR0 */
	pcie2_write32(pcie2, BCMA_CORE_PCIE2_CONFIGINDADDR, 0x844);
	pcie2_write32(pcie2, BCMA_CORE_PCIE2_CONFIGINDDATA, 0x883c883c);
	/* LTR1 */
	pcie2_write32(pcie2, BCMA_CORE_PCIE2_CONFIGINDADDR, 0x848);
	pcie2_write32(pcie2, BCMA_CORE_PCIE2_CONFIGINDDATA, 0x88648864);
	/* LTR2 */
	pcie2_write32(pcie2, BCMA_CORE_PCIE2_CONFIGINDADDR, 0x84C);
	pcie2_write32(pcie2, BCMA_CORE_PCIE2_CONFIGINDDATA, 0x90039003);
}