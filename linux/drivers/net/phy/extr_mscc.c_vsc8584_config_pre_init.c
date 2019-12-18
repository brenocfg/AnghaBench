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
typedef  int u16 ;
struct reg_val {int member_0; int member_1; int /*<<< orphan*/  val; int /*<<< orphan*/  reg; } ;
struct device {int dummy; } ;
struct TYPE_2__ {struct device dev; } ;
struct phy_device {TYPE_1__ mdio; } ;
struct firmware {scalar_t__ size; } ;

/* Variables and functions */
 unsigned int ARRAY_SIZE (struct reg_val const*) ; 
 int /*<<< orphan*/  MII_VSC85XX_INT_MASK ; 
 int /*<<< orphan*/  MSCC_EXT_PAGE_ACCESS ; 
 int /*<<< orphan*/  MSCC_PHY_BYPASS_CONTROL ; 
 int /*<<< orphan*/  MSCC_PHY_CU_PMD_TX_CNTL ; 
 int /*<<< orphan*/  MSCC_PHY_EXT_CNTL_STATUS ; 
 int MSCC_PHY_PAGE_EXTENDED_2 ; 
 int MSCC_PHY_PAGE_EXTENDED_3 ; 
 int MSCC_PHY_PAGE_STANDARD ; 
 int MSCC_PHY_PAGE_TEST ; 
 int MSCC_PHY_PAGE_TR ; 
 int /*<<< orphan*/  MSCC_PHY_SERDES_TX_CRC_ERR_CNT ; 
 int /*<<< orphan*/  MSCC_PHY_TEST_PAGE_5 ; 
 int /*<<< orphan*/  MSCC_PHY_TEST_PAGE_8 ; 
 int /*<<< orphan*/  MSCC_PHY_TR_CNTL ; 
 int /*<<< orphan*/  MSCC_PHY_TR_MSB ; 
 int /*<<< orphan*/  MSCC_VSC8584_REVB_INT8051_FW ; 
 int MSCC_VSC8584_REVB_INT8051_FW_CRC ; 
 int /*<<< orphan*/  MSCC_VSC8584_REVB_INT8051_FW_START_ADDR ; 
 int PARALLEL_DET_IGNORE_ADVERTISED ; 
 int SMI_BROADCAST_WR_EN ; 
 int TR_ADDR (int) ; 
 int TR_WRITE ; 
 int /*<<< orphan*/  dev_dbg (struct device*,char*) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  dev_warn (struct device*,char*) ; 
 int phy_base_read (struct phy_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  phy_base_write (struct phy_device*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  release_firmware (struct firmware const*) ; 
 int request_firmware (struct firmware const**,int /*<<< orphan*/ ,struct device*) ; 
 int /*<<< orphan*/  vsc8584_csr_write (struct phy_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int vsc8584_get_fw_crc (struct phy_device*,int /*<<< orphan*/ ,scalar_t__,int*) ; 
 int vsc8584_micro_assert_reset (struct phy_device*) ; 
 int /*<<< orphan*/  vsc8584_micro_deassert_reset (struct phy_device*,int) ; 
 scalar_t__ vsc8584_patch_fw (struct phy_device*,struct firmware const*) ; 

__attribute__((used)) static int vsc8584_config_pre_init(struct phy_device *phydev)
{
	const struct reg_val pre_init1[] = {
		{0x07fa, 0x0050100f},
		{0x1688, 0x00049f81},
		{0x0f90, 0x00688980},
		{0x03a4, 0x0000d8f0},
		{0x0fc0, 0x00000400},
		{0x0f82, 0x0012b002},
		{0x1686, 0x00000004},
		{0x168c, 0x00d2c46f},
		{0x17a2, 0x00000620},
		{0x16a0, 0x00eeffdd},
		{0x16a6, 0x00071448},
		{0x16a4, 0x0013132f},
		{0x16a8, 0x00000000},
		{0x0ffc, 0x00c0a028},
		{0x0fe8, 0x0091b06c},
		{0x0fea, 0x00041600},
		{0x0f80, 0x00fffaff},
		{0x0fec, 0x00901809},
		{0x0ffe, 0x00b01007},
		{0x16b0, 0x00eeff00},
		{0x16b2, 0x00007000},
		{0x16b4, 0x00000814},
	};
	const struct reg_val pre_init2[] = {
		{0x0486, 0x0008a518},
		{0x0488, 0x006dc696},
		{0x048a, 0x00000912},
	};
	const struct firmware *fw;
	struct device *dev = &phydev->mdio.dev;
	unsigned int i;
	u16 crc, reg;
	int ret;

	phy_base_write(phydev, MSCC_EXT_PAGE_ACCESS, MSCC_PHY_PAGE_STANDARD);

	/* all writes below are broadcasted to all PHYs in the same package */
	reg = phy_base_read(phydev, MSCC_PHY_EXT_CNTL_STATUS);
	reg |= SMI_BROADCAST_WR_EN;
	phy_base_write(phydev, MSCC_PHY_EXT_CNTL_STATUS, reg);

	phy_base_write(phydev, MII_VSC85XX_INT_MASK, 0);

	reg = phy_base_read(phydev,  MSCC_PHY_BYPASS_CONTROL);
	reg |= PARALLEL_DET_IGNORE_ADVERTISED;
	phy_base_write(phydev, MSCC_PHY_BYPASS_CONTROL, reg);

	/* The below register writes are tweaking analog and electrical
	 * configuration that were determined through characterization by PHY
	 * engineers. These don't mean anything more than "these are the best
	 * values".
	 */
	phy_base_write(phydev, MSCC_EXT_PAGE_ACCESS, MSCC_PHY_PAGE_EXTENDED_3);

	phy_base_write(phydev, MSCC_PHY_SERDES_TX_CRC_ERR_CNT, 0x2000);

	phy_base_write(phydev, MSCC_EXT_PAGE_ACCESS, MSCC_PHY_PAGE_TEST);

	phy_base_write(phydev, MSCC_PHY_TEST_PAGE_5, 0x1f20);

	reg = phy_base_read(phydev, MSCC_PHY_TEST_PAGE_8);
	reg |= 0x8000;
	phy_base_write(phydev, MSCC_PHY_TEST_PAGE_8, reg);

	phy_base_write(phydev, MSCC_EXT_PAGE_ACCESS, MSCC_PHY_PAGE_TR);

	phy_base_write(phydev, MSCC_PHY_TR_CNTL, TR_WRITE | TR_ADDR(0x2fa4));

	reg = phy_base_read(phydev, MSCC_PHY_TR_MSB);
	reg &= ~0x007f;
	reg |= 0x0019;
	phy_base_write(phydev, MSCC_PHY_TR_MSB, reg);

	phy_base_write(phydev, MSCC_PHY_TR_CNTL, TR_WRITE | TR_ADDR(0x0fa4));

	for (i = 0; i < ARRAY_SIZE(pre_init1); i++)
		vsc8584_csr_write(phydev, pre_init1[i].reg, pre_init1[i].val);

	phy_base_write(phydev, MSCC_EXT_PAGE_ACCESS, MSCC_PHY_PAGE_EXTENDED_2);

	phy_base_write(phydev, MSCC_PHY_CU_PMD_TX_CNTL, 0x028e);

	phy_base_write(phydev, MSCC_EXT_PAGE_ACCESS, MSCC_PHY_PAGE_TR);

	for (i = 0; i < ARRAY_SIZE(pre_init2); i++)
		vsc8584_csr_write(phydev, pre_init2[i].reg, pre_init2[i].val);

	phy_base_write(phydev, MSCC_EXT_PAGE_ACCESS, MSCC_PHY_PAGE_TEST);

	reg = phy_base_read(phydev, MSCC_PHY_TEST_PAGE_8);
	reg &= ~0x8000;
	phy_base_write(phydev, MSCC_PHY_TEST_PAGE_8, reg);

	phy_base_write(phydev, MSCC_EXT_PAGE_ACCESS, MSCC_PHY_PAGE_STANDARD);

	/* end of write broadcasting */
	reg = phy_base_read(phydev, MSCC_PHY_EXT_CNTL_STATUS);
	reg &= ~SMI_BROADCAST_WR_EN;
	phy_base_write(phydev, MSCC_PHY_EXT_CNTL_STATUS, reg);

	ret = request_firmware(&fw, MSCC_VSC8584_REVB_INT8051_FW, dev);
	if (ret) {
		dev_err(dev, "failed to load firmware %s, ret: %d\n",
			MSCC_VSC8584_REVB_INT8051_FW, ret);
		return ret;
	}

	/* Add one byte to size for the one added by the patch_fw function */
	ret = vsc8584_get_fw_crc(phydev,
				 MSCC_VSC8584_REVB_INT8051_FW_START_ADDR,
				 fw->size + 1, &crc);
	if (ret)
		goto out;

	if (crc != MSCC_VSC8584_REVB_INT8051_FW_CRC) {
		dev_dbg(dev, "FW CRC is not the expected one, patching FW\n");
		if (vsc8584_patch_fw(phydev, fw))
			dev_warn(dev,
				 "failed to patch FW, expect non-optimal device\n");
	}

	vsc8584_micro_deassert_reset(phydev, false);

	/* Add one byte to size for the one added by the patch_fw function */
	ret = vsc8584_get_fw_crc(phydev,
				 MSCC_VSC8584_REVB_INT8051_FW_START_ADDR,
				 fw->size + 1, &crc);
	if (ret)
		goto out;

	if (crc != MSCC_VSC8584_REVB_INT8051_FW_CRC)
		dev_warn(dev,
			 "FW CRC after patching is not the expected one, expect non-optimal device\n");

	ret = vsc8584_micro_assert_reset(phydev);
	if (ret)
		goto out;

	vsc8584_micro_deassert_reset(phydev, true);

out:
	phy_base_write(phydev, MSCC_EXT_PAGE_ACCESS, MSCC_PHY_PAGE_STANDARD);

	release_firmware(fw);

	return ret;
}