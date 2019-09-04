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
struct adapter {TYPE_1__ params; int /*<<< orphan*/  pdev; } ;

/* Variables and functions */
 scalar_t__ CHELSIO_CHIP_VERSION (int /*<<< orphan*/ ) ; 
 scalar_t__ CHELSIO_T5 ; 
 int /*<<< orphan*/  MYPF_REG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PL_INT_MAP0_A ; 
 int /*<<< orphan*/  PL_PF_INT_ENABLE_A ; 
 int /*<<< orphan*/  PL_WHOAMI_A ; 
 int SOURCEPF_G (int) ; 
 int T6_SOURCEPF_G (int) ; 
 scalar_t__ pci_channel_offline (int /*<<< orphan*/ ) ; 
 int t4_read_reg (struct adapter*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  t4_set_reg_field (struct adapter*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  t4_write_reg (struct adapter*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void t4_intr_disable(struct adapter *adapter)
{
	u32 whoami, pf;

	if (pci_channel_offline(adapter->pdev))
		return;

	whoami = t4_read_reg(adapter, PL_WHOAMI_A);
	pf = CHELSIO_CHIP_VERSION(adapter->params.chip) <= CHELSIO_T5 ?
			SOURCEPF_G(whoami) : T6_SOURCEPF_G(whoami);

	t4_write_reg(adapter, MYPF_REG(PL_PF_INT_ENABLE_A), 0);
	t4_set_reg_field(adapter, PL_INT_MAP0_A, 1 << pf, 0);
}