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
struct mlme_ext_info {int /*<<< orphan*/  bcn_interval; } ;
struct mlme_ext_priv {struct mlme_ext_info mlmext_info; } ;
struct adapter {struct mlme_ext_priv mlmeextpriv; } ;

/* Variables and functions */
 int BIT (int) ; 
 int /*<<< orphan*/  REG_ATIMWND ; 
 int /*<<< orphan*/  REG_BCN_CTRL ; 
 int /*<<< orphan*/  REG_BCN_INTERVAL ; 
 int /*<<< orphan*/  REG_RXTSF_OFFSET_CCK ; 
 int /*<<< orphan*/  REG_RXTSF_OFFSET_OFDM ; 
 int /*<<< orphan*/  REG_SLOT ; 
 int /*<<< orphan*/  REG_TCR ; 
 int /*<<< orphan*/  ResumeTxBeacon (struct adapter*) ; 
 int /*<<< orphan*/  TSFRST ; 
 int /*<<< orphan*/  _BeaconFunctionEnable (struct adapter*,int,int) ; 
 int /*<<< orphan*/  _InitBeaconParameters (struct adapter*) ; 
 int /*<<< orphan*/  usb_read32 (struct adapter*,int /*<<< orphan*/ ) ; 
 int usb_read8 (struct adapter*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_write16 (struct adapter*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_write32 (struct adapter*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_write8 (struct adapter*,int /*<<< orphan*/ ,int) ; 

void beacon_timing_control(struct adapter *adapt)
{
	u32 value32;
	struct mlme_ext_priv	*pmlmeext = &adapt->mlmeextpriv;
	struct mlme_ext_info	*pmlmeinfo = &pmlmeext->mlmext_info;
	u32 bcn_ctrl_reg			= REG_BCN_CTRL;
	/* reset TSF, enable update TSF, correcting TSF On Beacon */

	/* BCN interval */
	usb_write16(adapt, REG_BCN_INTERVAL, pmlmeinfo->bcn_interval);
	usb_write8(adapt, REG_ATIMWND, 0x02);/*  2ms */

	_InitBeaconParameters(adapt);

	usb_write8(adapt, REG_SLOT, 0x09);

	value32 = usb_read32(adapt, REG_TCR);
	value32 &= ~TSFRST;
	usb_write32(adapt,  REG_TCR, value32);

	value32 |= TSFRST;
	usb_write32(adapt, REG_TCR, value32);

	/*  NOTE: Fix test chip's bug (about contention windows's randomness) */
	usb_write8(adapt,  REG_RXTSF_OFFSET_CCK, 0x50);
	usb_write8(adapt, REG_RXTSF_OFFSET_OFDM, 0x50);

	_BeaconFunctionEnable(adapt, true, true);

	ResumeTxBeacon(adapt);

	usb_write8(adapt, bcn_ctrl_reg, usb_read8(adapt, bcn_ctrl_reg) | BIT(1));
}