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
typedef  int /*<<< orphan*/  u32 ;
struct isci_phy {TYPE_1__* link_layer_registers; } ;
struct TYPE_2__ {int /*<<< orphan*/  phy_configuration; } ;

/* Variables and functions */
 int /*<<< orphan*/  SCIC_SDS_REMOTE_NODE_CONTEXT_INVALID_INDEX ; 
 int /*<<< orphan*/  SCU_SAS_PCFG_GEN_BIT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SUSPEND_PROTOCOL_ENGINE ; 
 int /*<<< orphan*/  readl (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sci_phy_setup_transport (struct isci_phy*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void sci_phy_suspend(struct isci_phy *iphy)
{
	u32 scu_sas_pcfg_value;

	scu_sas_pcfg_value =
		readl(&iphy->link_layer_registers->phy_configuration);
	scu_sas_pcfg_value |= SCU_SAS_PCFG_GEN_BIT(SUSPEND_PROTOCOL_ENGINE);
	writel(scu_sas_pcfg_value,
		&iphy->link_layer_registers->phy_configuration);

	sci_phy_setup_transport(iphy, SCIC_SDS_REMOTE_NODE_CONTEXT_INVALID_INDEX);
}