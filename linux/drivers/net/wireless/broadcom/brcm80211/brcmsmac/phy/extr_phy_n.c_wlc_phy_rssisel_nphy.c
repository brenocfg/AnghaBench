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
typedef  scalar_t__ u8 ;
typedef  int u16 ;
struct TYPE_2__ {scalar_t__ phy_corenum; int /*<<< orphan*/  phy_rev; } ;
struct brcms_phy {int /*<<< orphan*/  radio_chanspec; TYPE_1__ pubpi; } ;

/* Variables and functions */
 scalar_t__ CHSPEC_IS5G (int /*<<< orphan*/ ) ; 
 scalar_t__ NPHY_RSSI_SEL_IQ ; 
 scalar_t__ NPHY_RSSI_SEL_NB ; 
 scalar_t__ NPHY_RSSI_SEL_TBD ; 
 scalar_t__ NPHY_RSSI_SEL_W1 ; 
 scalar_t__ NPHY_RSSI_SEL_W2 ; 
 scalar_t__ NREV_GE (int /*<<< orphan*/ ,int) ; 
 scalar_t__ PHY_CORE_0 ; 
 scalar_t__ PHY_CORE_1 ; 
 scalar_t__ RADIO_MIMO_CORESEL_CORE1 ; 
 scalar_t__ RADIO_MIMO_CORESEL_CORE2 ; 
 scalar_t__ RADIO_MIMO_CORESEL_OFF ; 
 int /*<<< orphan*/  brcms_phy_wr_tx_mux (struct brcms_phy*,scalar_t__) ; 
 int /*<<< orphan*/  mod_phy_reg (struct brcms_phy*,int,int,int) ; 
 int /*<<< orphan*/  udelay (int) ; 

void wlc_phy_rssisel_nphy(struct brcms_phy *pi, u8 core_code, u8 rssi_type)
{
	u16 mask, val;
	u16 afectrlovr_rssi_val, rfctrlcmd_rxen_val, rfctrlcmd_coresel_val,
	    startseq;
	u16 rfctrlovr_rssi_val, rfctrlovr_rxen_val, rfctrlovr_coresel_val,
	    rfctrlovr_trigger_val;
	u16 afectrlovr_rssi_mask, rfctrlcmd_mask, rfctrlovr_mask;
	u16 rfctrlcmd_val, rfctrlovr_val;
	u8 core;

	if (NREV_GE(pi->pubpi.phy_rev, 3)) {
		if (core_code == RADIO_MIMO_CORESEL_OFF) {
			mod_phy_reg(pi, 0x8f, (0x1 << 9), 0);
			mod_phy_reg(pi, 0xa5, (0x1 << 9), 0);

			mod_phy_reg(pi, 0xa6, (0x3 << 8), 0);
			mod_phy_reg(pi, 0xa7, (0x3 << 8), 0);

			mod_phy_reg(pi, 0xe5, (0x1 << 5), 0);
			mod_phy_reg(pi, 0xe6, (0x1 << 5), 0);

			mask = (0x1 << 2) |
			       (0x1 << 3) | (0x1 << 4) | (0x1 << 5);
			mod_phy_reg(pi, 0xf9, mask, 0);
			mod_phy_reg(pi, 0xfb, mask, 0);

		} else {
			for (core = 0; core < pi->pubpi.phy_corenum; core++) {
				if (core_code == RADIO_MIMO_CORESEL_CORE1
				    && core == PHY_CORE_1)
					continue;
				else if (core_code == RADIO_MIMO_CORESEL_CORE2
					 && core == PHY_CORE_0)
					continue;

				mod_phy_reg(pi, (core == PHY_CORE_0) ?
					    0x8f : 0xa5, (0x1 << 9), 1 << 9);

				if (rssi_type == NPHY_RSSI_SEL_W1 ||
				    rssi_type == NPHY_RSSI_SEL_W2 ||
				    rssi_type == NPHY_RSSI_SEL_NB) {
					mod_phy_reg(pi,
						    (core ==
						     PHY_CORE_0) ? 0xa6 : 0xa7,
						    (0x3 << 8), 0);

					mask = (0x1 << 2) |
					       (0x1 << 3) |
					       (0x1 << 4) | (0x1 << 5);
					mod_phy_reg(pi,
						    (core ==
						     PHY_CORE_0) ? 0xf9 : 0xfb,
						    mask, 0);

					if (rssi_type == NPHY_RSSI_SEL_W1) {
						if (CHSPEC_IS5G(
							  pi->radio_chanspec)) {
							mask = (0x1 << 2);
							val = 1 << 2;
						} else {
							mask = (0x1 << 3);
							val = 1 << 3;
						}
					} else if (rssi_type ==
						   NPHY_RSSI_SEL_W2) {
						mask = (0x1 << 4);
						val = 1 << 4;
					} else {
						mask = (0x1 << 5);
						val = 1 << 5;
					}
					mod_phy_reg(pi,
						    (core ==
						     PHY_CORE_0) ? 0xf9 : 0xfb,
						    mask, val);

					mask = (0x1 << 5);
					val = 1 << 5;
					mod_phy_reg(pi, (core == PHY_CORE_0) ?
						    0xe5 : 0xe6, mask, val);
				} else {
					if (rssi_type == NPHY_RSSI_SEL_TBD) {
						mask = (0x3 << 8);
						val = 1 << 8;
						mod_phy_reg(pi,
							    (core ==
							     PHY_CORE_0) ? 0xa6
							    : 0xa7, mask, val);
						mask = (0x3 << 10);
						val = 1 << 10;
						mod_phy_reg(pi,
							    (core ==
							     PHY_CORE_0) ? 0xa6
							    : 0xa7, mask, val);
					} else if (rssi_type ==
						   NPHY_RSSI_SEL_IQ) {
						mask = (0x3 << 8);
						val = 2 << 8;
						mod_phy_reg(pi,
							    (core ==
							     PHY_CORE_0) ? 0xa6
							    : 0xa7, mask, val);
						mask = (0x3 << 10);
						val = 2 << 10;
						mod_phy_reg(pi,
							    (core ==
							     PHY_CORE_0) ? 0xa6
							    : 0xa7, mask, val);
					} else {
						mask = (0x3 << 8);
						val = 3 << 8;
						mod_phy_reg(pi,
							    (core ==
							     PHY_CORE_0) ? 0xa6
							    : 0xa7, mask, val);
						mask = (0x3 << 10);
						val = 3 << 10;
						mod_phy_reg(pi,
							    (core ==
							     PHY_CORE_0) ? 0xa6
							    : 0xa7, mask, val);
						brcms_phy_wr_tx_mux(pi, core);
						afectrlovr_rssi_val = 1 << 9;
						mod_phy_reg(pi,
							   (core ==
							    PHY_CORE_0) ? 0x8f
							   : 0xa5, (0x1 << 9),
							   afectrlovr_rssi_val);
					}
				}
			}
		}
	} else {

		if ((rssi_type == NPHY_RSSI_SEL_W1) ||
		    (rssi_type == NPHY_RSSI_SEL_W2) ||
		    (rssi_type == NPHY_RSSI_SEL_NB))
			val = 0x0;
		else if (rssi_type == NPHY_RSSI_SEL_TBD)
			val = 0x1;
		else if (rssi_type == NPHY_RSSI_SEL_IQ)
			val = 0x2;
		else
			val = 0x3;

		mask = ((0x3 << 12) | (0x3 << 14));
		val = (val << 12) | (val << 14);
		mod_phy_reg(pi, 0xa6, mask, val);
		mod_phy_reg(pi, 0xa7, mask, val);

		if ((rssi_type == NPHY_RSSI_SEL_W1) ||
		    (rssi_type == NPHY_RSSI_SEL_W2) ||
		    (rssi_type == NPHY_RSSI_SEL_NB)) {
			if (rssi_type == NPHY_RSSI_SEL_W1)
				val = 0x1;
			if (rssi_type == NPHY_RSSI_SEL_W2)
				val = 0x2;
			if (rssi_type == NPHY_RSSI_SEL_NB)
				val = 0x3;

			mask = (0x3 << 4);
			val = (val << 4);
			mod_phy_reg(pi, 0x7a, mask, val);
			mod_phy_reg(pi, 0x7d, mask, val);
		}

		if (core_code == RADIO_MIMO_CORESEL_OFF) {
			afectrlovr_rssi_val = 0;
			rfctrlcmd_rxen_val = 0;
			rfctrlcmd_coresel_val = 0;
			rfctrlovr_rssi_val = 0;
			rfctrlovr_rxen_val = 0;
			rfctrlovr_coresel_val = 0;
			rfctrlovr_trigger_val = 0;
			startseq = 0;
		} else {
			afectrlovr_rssi_val = 1;
			rfctrlcmd_rxen_val = 1;
			rfctrlcmd_coresel_val = core_code;
			rfctrlovr_rssi_val = 1;
			rfctrlovr_rxen_val = 1;
			rfctrlovr_coresel_val = 1;
			rfctrlovr_trigger_val = 1;
			startseq = 1;
		}

		afectrlovr_rssi_mask = ((0x1 << 12) | (0x1 << 13));
		afectrlovr_rssi_val = (afectrlovr_rssi_val <<
				       12) | (afectrlovr_rssi_val << 13);
		mod_phy_reg(pi, 0xa5, afectrlovr_rssi_mask,
			    afectrlovr_rssi_val);

		if ((rssi_type == NPHY_RSSI_SEL_W1) ||
		    (rssi_type == NPHY_RSSI_SEL_W2) ||
		    (rssi_type == NPHY_RSSI_SEL_NB)) {
			rfctrlcmd_mask = ((0x1 << 8) | (0x7 << 3));
			rfctrlcmd_val = (rfctrlcmd_rxen_val << 8) |
					(rfctrlcmd_coresel_val << 3);

			rfctrlovr_mask = ((0x1 << 5) |
					  (0x1 << 12) |
					  (0x1 << 1) | (0x1 << 0));
			rfctrlovr_val = (rfctrlovr_rssi_val <<
					 5) |
					(rfctrlovr_rxen_val << 12) |
					(rfctrlovr_coresel_val << 1) |
					(rfctrlovr_trigger_val << 0);

			mod_phy_reg(pi, 0x78, rfctrlcmd_mask, rfctrlcmd_val);
			mod_phy_reg(pi, 0xec, rfctrlovr_mask, rfctrlovr_val);

			mod_phy_reg(pi, 0x78, (0x1 << 0), (startseq << 0));
			udelay(20);

			mod_phy_reg(pi, 0xec, (0x1 << 0), 0);
		}
	}
}