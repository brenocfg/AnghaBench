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
struct phy_device {int dummy; } ;

/* Variables and functions */
 int lan88xx_TR_reg_set (struct phy_device*,int,int) ; 
 int /*<<< orphan*/  phydev_warn (struct phy_device*,char*) ; 

__attribute__((used)) static void lan88xx_config_TR_regs(struct phy_device *phydev)
{
	int err;

	/* Get access to Channel 0x1, Node 0xF , Register 0x01.
	 * Write 24-bit value 0x12B00A to register. Setting MrvlTrFix1000Kf,
	 * MrvlTrFix1000Kp, MasterEnableTR bits.
	 */
	err = lan88xx_TR_reg_set(phydev, 0x0F82, 0x12B00A);
	if (err < 0)
		phydev_warn(phydev, "Failed to Set Register[0x0F82]\n");

	/* Get access to Channel b'10, Node b'1101, Register 0x06.
	 * Write 24-bit value 0xD2C46F to register. Setting SSTrKf1000Slv,
	 * SSTrKp1000Mas bits.
	 */
	err = lan88xx_TR_reg_set(phydev, 0x168C, 0xD2C46F);
	if (err < 0)
		phydev_warn(phydev, "Failed to Set Register[0x168C]\n");

	/* Get access to Channel b'10, Node b'1111, Register 0x11.
	 * Write 24-bit value 0x620 to register. Setting rem_upd_done_thresh
	 * bits
	 */
	err = lan88xx_TR_reg_set(phydev, 0x17A2, 0x620);
	if (err < 0)
		phydev_warn(phydev, "Failed to Set Register[0x17A2]\n");

	/* Get access to Channel b'10, Node b'1101, Register 0x10.
	 * Write 24-bit value 0xEEFFDD to register. Setting
	 * eee_TrKp1Long_1000, eee_TrKp2Long_1000, eee_TrKp3Long_1000,
	 * eee_TrKp1Short_1000,eee_TrKp2Short_1000, eee_TrKp3Short_1000 bits.
	 */
	err = lan88xx_TR_reg_set(phydev, 0x16A0, 0xEEFFDD);
	if (err < 0)
		phydev_warn(phydev, "Failed to Set Register[0x16A0]\n");

	/* Get access to Channel b'10, Node b'1101, Register 0x13.
	 * Write 24-bit value 0x071448 to register. Setting
	 * slv_lpi_tr_tmr_val1, slv_lpi_tr_tmr_val2 bits.
	 */
	err = lan88xx_TR_reg_set(phydev, 0x16A6, 0x071448);
	if (err < 0)
		phydev_warn(phydev, "Failed to Set Register[0x16A6]\n");

	/* Get access to Channel b'10, Node b'1101, Register 0x12.
	 * Write 24-bit value 0x13132F to register. Setting
	 * slv_sigdet_timer_val1, slv_sigdet_timer_val2 bits.
	 */
	err = lan88xx_TR_reg_set(phydev, 0x16A4, 0x13132F);
	if (err < 0)
		phydev_warn(phydev, "Failed to Set Register[0x16A4]\n");

	/* Get access to Channel b'10, Node b'1101, Register 0x14.
	 * Write 24-bit value 0x0 to register. Setting eee_3level_delay,
	 * eee_TrKf_freeze_delay bits.
	 */
	err = lan88xx_TR_reg_set(phydev, 0x16A8, 0x0);
	if (err < 0)
		phydev_warn(phydev, "Failed to Set Register[0x16A8]\n");

	/* Get access to Channel b'01, Node b'1111, Register 0x34.
	 * Write 24-bit value 0x91B06C to register. Setting
	 * FastMseSearchThreshLong1000, FastMseSearchThreshShort1000,
	 * FastMseSearchUpdGain1000 bits.
	 */
	err = lan88xx_TR_reg_set(phydev, 0x0FE8, 0x91B06C);
	if (err < 0)
		phydev_warn(phydev, "Failed to Set Register[0x0FE8]\n");

	/* Get access to Channel b'01, Node b'1111, Register 0x3E.
	 * Write 24-bit value 0xC0A028 to register. Setting
	 * FastMseKp2ThreshLong1000, FastMseKp2ThreshShort1000,
	 * FastMseKp2UpdGain1000, FastMseKp2ExitEn1000 bits.
	 */
	err = lan88xx_TR_reg_set(phydev, 0x0FFC, 0xC0A028);
	if (err < 0)
		phydev_warn(phydev, "Failed to Set Register[0x0FFC]\n");

	/* Get access to Channel b'01, Node b'1111, Register 0x35.
	 * Write 24-bit value 0x041600 to register. Setting
	 * FastMseSearchPhShNum1000, FastMseSearchClksPerPh1000,
	 * FastMsePhChangeDelay1000 bits.
	 */
	err = lan88xx_TR_reg_set(phydev, 0x0FEA, 0x041600);
	if (err < 0)
		phydev_warn(phydev, "Failed to Set Register[0x0FEA]\n");

	/* Get access to Channel b'10, Node b'1101, Register 0x03.
	 * Write 24-bit value 0x000004 to register. Setting TrFreeze bits.
	 */
	err = lan88xx_TR_reg_set(phydev, 0x1686, 0x000004);
	if (err < 0)
		phydev_warn(phydev, "Failed to Set Register[0x1686]\n");
}