#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct TYPE_2__ {int /*<<< orphan*/  chip; } ;
struct adapter {TYPE_1__ params; int /*<<< orphan*/  pf; } ;

/* Variables and functions */
 scalar_t__ CHELSIO_CHIP_VERSION (int /*<<< orphan*/ ) ; 
 scalar_t__ CHELSIO_T5 ; 
 int ENABLE_F ; 
 int FUNCTION_V (int /*<<< orphan*/ ) ; 
 int LOCALCFG_F ; 
 int /*<<< orphan*/  PCIE_CFG_SPACE_DATA_A ; 
 int /*<<< orphan*/  PCIE_CFG_SPACE_REQ_A ; 
 int REGISTER_V (int) ; 
 int T6_ENABLE_F ; 
 scalar_t__ is_t4 (int /*<<< orphan*/ ) ; 
 int t4_read_reg (struct adapter*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  t4_write_reg (struct adapter*,int /*<<< orphan*/ ,int) ; 

void t4_hw_pci_read_cfg4(struct adapter *adap, int reg, u32 *val)
{
	u32 req = FUNCTION_V(adap->pf) | REGISTER_V(reg);

	if (CHELSIO_CHIP_VERSION(adap->params.chip) <= CHELSIO_T5)
		req |= ENABLE_F;
	else
		req |= T6_ENABLE_F;

	if (is_t4(adap->params.chip))
		req |= LOCALCFG_F;

	t4_write_reg(adap, PCIE_CFG_SPACE_REQ_A, req);
	*val = t4_read_reg(adap, PCIE_CFG_SPACE_DATA_A);

	/* Reset ENABLE to 0 so reads of PCIE_CFG_SPACE_DATA won't cause a
	 * Configuration Space read.  (None of the other fields matter when
	 * ENABLE is 0 so a simple register write is easier than a
	 * read-modify-write via t4_set_reg_field().)
	 */
	t4_write_reg(adap, PCIE_CFG_SPACE_REQ_A, 0);
}