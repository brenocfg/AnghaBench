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
struct pch_gbe_hw {TYPE_1__* reg; } ;
struct pch_gbe_adapter {struct pch_gbe_hw hw; } ;
struct TYPE_2__ {int /*<<< orphan*/  TCPIP_ACC; int /*<<< orphan*/  TX_MODE; } ;

/* Variables and functions */
 int PCH_GBE_TM_LONG_PKT ; 
 int PCH_GBE_TM_SHORT_PKT ; 
 int PCH_GBE_TM_ST_AND_FD ; 
 int PCH_GBE_TM_TH_ALM_EMP_4 ; 
 int PCH_GBE_TM_TH_ALM_FULL_8 ; 
 int PCH_GBE_TM_TH_TX_STRT_8 ; 
 int PCH_GBE_TX_TCPIPACC_EN ; 
 int ioread32 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  iowrite32 (int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void pch_gbe_setup_tctl(struct pch_gbe_adapter *adapter)
{
	struct pch_gbe_hw *hw = &adapter->hw;
	u32 tx_mode, tcpip;

	tx_mode = PCH_GBE_TM_LONG_PKT |
		PCH_GBE_TM_ST_AND_FD |
		PCH_GBE_TM_SHORT_PKT |
		PCH_GBE_TM_TH_TX_STRT_8 |
		PCH_GBE_TM_TH_ALM_EMP_4 | PCH_GBE_TM_TH_ALM_FULL_8;

	iowrite32(tx_mode, &hw->reg->TX_MODE);

	tcpip = ioread32(&hw->reg->TCPIP_ACC);
	tcpip |= PCH_GBE_TX_TCPIPACC_EN;
	iowrite32(tcpip, &hw->reg->TCPIP_ACC);
	return;
}