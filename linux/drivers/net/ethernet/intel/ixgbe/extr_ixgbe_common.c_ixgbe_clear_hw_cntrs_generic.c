#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int u16 ;
struct TYPE_5__ {int /*<<< orphan*/  (* read_reg ) (struct ixgbe_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ;int /*<<< orphan*/  (* identify ) (struct ixgbe_hw*) ;} ;
struct TYPE_6__ {scalar_t__ id; TYPE_2__ ops; } ;
struct TYPE_4__ {scalar_t__ type; } ;
struct ixgbe_hw {TYPE_3__ phy; TYPE_1__ mac; } ;
typedef  int /*<<< orphan*/  s32 ;

/* Variables and functions */
 int /*<<< orphan*/  IXGBE_BPRC ; 
 int /*<<< orphan*/  IXGBE_BPTC ; 
 int /*<<< orphan*/  IXGBE_CRCERRS ; 
 int /*<<< orphan*/  IXGBE_ERRBC ; 
 int /*<<< orphan*/  IXGBE_GORCH ; 
 int /*<<< orphan*/  IXGBE_GORCL ; 
 int /*<<< orphan*/  IXGBE_GOTCH ; 
 int /*<<< orphan*/  IXGBE_GOTCL ; 
 int /*<<< orphan*/  IXGBE_GPRC ; 
 int /*<<< orphan*/  IXGBE_GPTC ; 
 int /*<<< orphan*/  IXGBE_ILLERRC ; 
 int /*<<< orphan*/  IXGBE_LDPCECH ; 
 int /*<<< orphan*/  IXGBE_LDPCECL ; 
 int /*<<< orphan*/  IXGBE_LXOFFRXC ; 
 int /*<<< orphan*/  IXGBE_LXOFFRXCNT ; 
 int /*<<< orphan*/  IXGBE_LXOFFTXC ; 
 int /*<<< orphan*/  IXGBE_LXONRXC ; 
 int /*<<< orphan*/  IXGBE_LXONRXCNT ; 
 int /*<<< orphan*/  IXGBE_LXONTXC ; 
 int /*<<< orphan*/  IXGBE_MLFC ; 
 int /*<<< orphan*/  IXGBE_MNGPDC ; 
 int /*<<< orphan*/  IXGBE_MNGPRC ; 
 int /*<<< orphan*/  IXGBE_MNGPTC ; 
 int /*<<< orphan*/  IXGBE_MPC (int) ; 
 int /*<<< orphan*/  IXGBE_MPRC ; 
 int /*<<< orphan*/  IXGBE_MPTC ; 
 int /*<<< orphan*/  IXGBE_MRFC ; 
 int /*<<< orphan*/  IXGBE_MSPDC ; 
 int /*<<< orphan*/  IXGBE_PCRC8ECH ; 
 int /*<<< orphan*/  IXGBE_PCRC8ECL ; 
 int /*<<< orphan*/  IXGBE_PRC1023 ; 
 int /*<<< orphan*/  IXGBE_PRC127 ; 
 int /*<<< orphan*/  IXGBE_PRC1522 ; 
 int /*<<< orphan*/  IXGBE_PRC255 ; 
 int /*<<< orphan*/  IXGBE_PRC511 ; 
 int /*<<< orphan*/  IXGBE_PRC64 ; 
 int /*<<< orphan*/  IXGBE_PTC1023 ; 
 int /*<<< orphan*/  IXGBE_PTC127 ; 
 int /*<<< orphan*/  IXGBE_PTC1522 ; 
 int /*<<< orphan*/  IXGBE_PTC255 ; 
 int /*<<< orphan*/  IXGBE_PTC511 ; 
 int /*<<< orphan*/  IXGBE_PTC64 ; 
 int /*<<< orphan*/  IXGBE_PXOFFRXC (int) ; 
 int /*<<< orphan*/  IXGBE_PXOFFRXCNT (int) ; 
 int /*<<< orphan*/  IXGBE_PXOFFTXC (int) ; 
 int /*<<< orphan*/  IXGBE_PXON2OFFCNT (int) ; 
 int /*<<< orphan*/  IXGBE_PXONRXC (int) ; 
 int /*<<< orphan*/  IXGBE_PXONRXCNT (int) ; 
 int /*<<< orphan*/  IXGBE_PXONTXC (int) ; 
 int /*<<< orphan*/  IXGBE_QBRC (int) ; 
 int /*<<< orphan*/  IXGBE_QBRC_H (int) ; 
 int /*<<< orphan*/  IXGBE_QBRC_L (int) ; 
 int /*<<< orphan*/  IXGBE_QBTC (int) ; 
 int /*<<< orphan*/  IXGBE_QBTC_H (int) ; 
 int /*<<< orphan*/  IXGBE_QBTC_L (int) ; 
 int /*<<< orphan*/  IXGBE_QPRC (int) ; 
 int /*<<< orphan*/  IXGBE_QPRDC (int) ; 
 int /*<<< orphan*/  IXGBE_QPTC (int) ; 
 int /*<<< orphan*/  IXGBE_READ_REG (struct ixgbe_hw*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IXGBE_RFC ; 
 int /*<<< orphan*/  IXGBE_RJC ; 
 int /*<<< orphan*/  IXGBE_RLEC ; 
 int /*<<< orphan*/  IXGBE_RNBC (int) ; 
 int /*<<< orphan*/  IXGBE_ROC ; 
 int /*<<< orphan*/  IXGBE_RUC ; 
 int /*<<< orphan*/  IXGBE_TORH ; 
 int /*<<< orphan*/  IXGBE_TORL ; 
 int /*<<< orphan*/  IXGBE_TPR ; 
 int /*<<< orphan*/  IXGBE_TPT ; 
 int /*<<< orphan*/  MDIO_MMD_PCS ; 
 scalar_t__ ixgbe_mac_82598EB ; 
 scalar_t__ ixgbe_mac_82599EB ; 
 scalar_t__ ixgbe_mac_X540 ; 
 scalar_t__ ixgbe_mac_X550 ; 
 int /*<<< orphan*/  stub1 (struct ixgbe_hw*) ; 
 int /*<<< orphan*/  stub2 (struct ixgbe_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  stub3 (struct ixgbe_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  stub4 (struct ixgbe_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  stub5 (struct ixgbe_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 

s32 ixgbe_clear_hw_cntrs_generic(struct ixgbe_hw *hw)
{
	u16 i = 0;

	IXGBE_READ_REG(hw, IXGBE_CRCERRS);
	IXGBE_READ_REG(hw, IXGBE_ILLERRC);
	IXGBE_READ_REG(hw, IXGBE_ERRBC);
	IXGBE_READ_REG(hw, IXGBE_MSPDC);
	for (i = 0; i < 8; i++)
		IXGBE_READ_REG(hw, IXGBE_MPC(i));

	IXGBE_READ_REG(hw, IXGBE_MLFC);
	IXGBE_READ_REG(hw, IXGBE_MRFC);
	IXGBE_READ_REG(hw, IXGBE_RLEC);
	IXGBE_READ_REG(hw, IXGBE_LXONTXC);
	IXGBE_READ_REG(hw, IXGBE_LXOFFTXC);
	if (hw->mac.type >= ixgbe_mac_82599EB) {
		IXGBE_READ_REG(hw, IXGBE_LXONRXCNT);
		IXGBE_READ_REG(hw, IXGBE_LXOFFRXCNT);
	} else {
		IXGBE_READ_REG(hw, IXGBE_LXONRXC);
		IXGBE_READ_REG(hw, IXGBE_LXOFFRXC);
	}

	for (i = 0; i < 8; i++) {
		IXGBE_READ_REG(hw, IXGBE_PXONTXC(i));
		IXGBE_READ_REG(hw, IXGBE_PXOFFTXC(i));
		if (hw->mac.type >= ixgbe_mac_82599EB) {
			IXGBE_READ_REG(hw, IXGBE_PXONRXCNT(i));
			IXGBE_READ_REG(hw, IXGBE_PXOFFRXCNT(i));
		} else {
			IXGBE_READ_REG(hw, IXGBE_PXONRXC(i));
			IXGBE_READ_REG(hw, IXGBE_PXOFFRXC(i));
		}
	}
	if (hw->mac.type >= ixgbe_mac_82599EB)
		for (i = 0; i < 8; i++)
			IXGBE_READ_REG(hw, IXGBE_PXON2OFFCNT(i));
	IXGBE_READ_REG(hw, IXGBE_PRC64);
	IXGBE_READ_REG(hw, IXGBE_PRC127);
	IXGBE_READ_REG(hw, IXGBE_PRC255);
	IXGBE_READ_REG(hw, IXGBE_PRC511);
	IXGBE_READ_REG(hw, IXGBE_PRC1023);
	IXGBE_READ_REG(hw, IXGBE_PRC1522);
	IXGBE_READ_REG(hw, IXGBE_GPRC);
	IXGBE_READ_REG(hw, IXGBE_BPRC);
	IXGBE_READ_REG(hw, IXGBE_MPRC);
	IXGBE_READ_REG(hw, IXGBE_GPTC);
	IXGBE_READ_REG(hw, IXGBE_GORCL);
	IXGBE_READ_REG(hw, IXGBE_GORCH);
	IXGBE_READ_REG(hw, IXGBE_GOTCL);
	IXGBE_READ_REG(hw, IXGBE_GOTCH);
	if (hw->mac.type == ixgbe_mac_82598EB)
		for (i = 0; i < 8; i++)
			IXGBE_READ_REG(hw, IXGBE_RNBC(i));
	IXGBE_READ_REG(hw, IXGBE_RUC);
	IXGBE_READ_REG(hw, IXGBE_RFC);
	IXGBE_READ_REG(hw, IXGBE_ROC);
	IXGBE_READ_REG(hw, IXGBE_RJC);
	IXGBE_READ_REG(hw, IXGBE_MNGPRC);
	IXGBE_READ_REG(hw, IXGBE_MNGPDC);
	IXGBE_READ_REG(hw, IXGBE_MNGPTC);
	IXGBE_READ_REG(hw, IXGBE_TORL);
	IXGBE_READ_REG(hw, IXGBE_TORH);
	IXGBE_READ_REG(hw, IXGBE_TPR);
	IXGBE_READ_REG(hw, IXGBE_TPT);
	IXGBE_READ_REG(hw, IXGBE_PTC64);
	IXGBE_READ_REG(hw, IXGBE_PTC127);
	IXGBE_READ_REG(hw, IXGBE_PTC255);
	IXGBE_READ_REG(hw, IXGBE_PTC511);
	IXGBE_READ_REG(hw, IXGBE_PTC1023);
	IXGBE_READ_REG(hw, IXGBE_PTC1522);
	IXGBE_READ_REG(hw, IXGBE_MPTC);
	IXGBE_READ_REG(hw, IXGBE_BPTC);
	for (i = 0; i < 16; i++) {
		IXGBE_READ_REG(hw, IXGBE_QPRC(i));
		IXGBE_READ_REG(hw, IXGBE_QPTC(i));
		if (hw->mac.type >= ixgbe_mac_82599EB) {
			IXGBE_READ_REG(hw, IXGBE_QBRC_L(i));
			IXGBE_READ_REG(hw, IXGBE_QBRC_H(i));
			IXGBE_READ_REG(hw, IXGBE_QBTC_L(i));
			IXGBE_READ_REG(hw, IXGBE_QBTC_H(i));
			IXGBE_READ_REG(hw, IXGBE_QPRDC(i));
		} else {
			IXGBE_READ_REG(hw, IXGBE_QBRC(i));
			IXGBE_READ_REG(hw, IXGBE_QBTC(i));
		}
	}

	if (hw->mac.type == ixgbe_mac_X550 || hw->mac.type == ixgbe_mac_X540) {
		if (hw->phy.id == 0)
			hw->phy.ops.identify(hw);
		hw->phy.ops.read_reg(hw, IXGBE_PCRC8ECL, MDIO_MMD_PCS, &i);
		hw->phy.ops.read_reg(hw, IXGBE_PCRC8ECH, MDIO_MMD_PCS, &i);
		hw->phy.ops.read_reg(hw, IXGBE_LDPCECL, MDIO_MMD_PCS, &i);
		hw->phy.ops.read_reg(hw, IXGBE_LDPCECH, MDIO_MMD_PCS, &i);
	}

	return 0;
}