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
struct rtsx_pcr {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  D3_DELINK_MODE_EN ; 
 int /*<<< orphan*/  IC_VER_A ; 
 int /*<<< orphan*/  RTS524A_PM_CTRL3 ; 
 int /*<<< orphan*/  _PHY_ANA03 ; 
 int _PHY_ANA03_OOBS_DEB_EN ; 
 int _PHY_ANA03_TIMER_MAX ; 
 int _PHY_CMU_DEBUG_EN ; 
 int /*<<< orphan*/  _PHY_FLD0 ; 
 int _PHY_FLD0_BER_COUNT ; 
 int _PHY_FLD0_BER_TIMER ; 
 int _PHY_FLD0_BIT_ERR_RSTN ; 
 int _PHY_FLD0_CHECK_EN ; 
 int _PHY_FLD0_CLK_REQ_20C ; 
 int _PHY_FLD0_RX_IDLE_EN ; 
 int /*<<< orphan*/  _PHY_REV0 ; 
 int _PHY_REV0_CDR_BYPASS_PFD ; 
 int _PHY_REV0_CDR_RX_IDLE_BYPASS ; 
 int _PHY_REV0_FILTER_OUT ; 
 scalar_t__ is_version (struct rtsx_pcr*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtsx_pci_write_phy_register (struct rtsx_pcr*,int /*<<< orphan*/ ,int) ; 
 int rtsx_pci_write_register (struct rtsx_pcr*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int rts525a_optimize_phy(struct rtsx_pcr *pcr)
{
	int err;

	err = rtsx_pci_write_register(pcr, RTS524A_PM_CTRL3,
		D3_DELINK_MODE_EN, 0x00);
	if (err < 0)
		return err;

	rtsx_pci_write_phy_register(pcr, _PHY_FLD0,
		_PHY_FLD0_CLK_REQ_20C | _PHY_FLD0_RX_IDLE_EN |
		_PHY_FLD0_BIT_ERR_RSTN | _PHY_FLD0_BER_COUNT |
		_PHY_FLD0_BER_TIMER | _PHY_FLD0_CHECK_EN);

	rtsx_pci_write_phy_register(pcr, _PHY_ANA03,
		_PHY_ANA03_TIMER_MAX | _PHY_ANA03_OOBS_DEB_EN |
		_PHY_CMU_DEBUG_EN);

	if (is_version(pcr, 0x525A, IC_VER_A))
		rtsx_pci_write_phy_register(pcr, _PHY_REV0,
			_PHY_REV0_FILTER_OUT | _PHY_REV0_CDR_BYPASS_PFD |
			_PHY_REV0_CDR_RX_IDLE_BYPASS);

	return 0;
}