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
struct b43_wldev {int dummy; } ;
struct b43_nphy_channeltab_entry_rev2 {int /*<<< orphan*/  radio_c2_tx_mxbgtrim; int /*<<< orphan*/  radio_c2_tx_pgapadtn; int /*<<< orphan*/  radio_c2_rx_rfr1; int /*<<< orphan*/  radio_c2_lgbuf_gtune; int /*<<< orphan*/  radio_c2_lgbuf_atune; int /*<<< orphan*/  radio_c1_tx_mxbgtrim; int /*<<< orphan*/  radio_c1_tx_pgapadtn; int /*<<< orphan*/  radio_c1_rx_rfr1; int /*<<< orphan*/  radio_c1_lgbuf_gtune; int /*<<< orphan*/  radio_c1_lgbuf_atune; int /*<<< orphan*/  radio_lgen_tune2; int /*<<< orphan*/  radio_lgen_tune1; int /*<<< orphan*/  radio_lgbuf_cenbuf; int /*<<< orphan*/  radio_pll_lfc2; int /*<<< orphan*/  radio_pll_lfr1; int /*<<< orphan*/  radio_pll_lfc1; int /*<<< orphan*/  radio_vco_cal2; int /*<<< orphan*/  radio_vco_cal1; int /*<<< orphan*/  radio_vco_captail; int /*<<< orphan*/  radio_rf_pllmod1; int /*<<< orphan*/  radio_rf_pllmod0; int /*<<< orphan*/  radio_pll_ref; } ;

/* Variables and functions */
 int /*<<< orphan*/  B2055_C1_LGBUF_ATUNE ; 
 int /*<<< orphan*/  B2055_C1_LGBUF_GTUNE ; 
 int /*<<< orphan*/  B2055_C1_RX_RFR1 ; 
 int /*<<< orphan*/  B2055_C1_TX_MXBGTRIM ; 
 int /*<<< orphan*/  B2055_C1_TX_PGAPADTN ; 
 int /*<<< orphan*/  B2055_C2_LGBUF_ATUNE ; 
 int /*<<< orphan*/  B2055_C2_LGBUF_GTUNE ; 
 int /*<<< orphan*/  B2055_C2_RX_RFR1 ; 
 int /*<<< orphan*/  B2055_C2_TX_MXBGTRIM ; 
 int /*<<< orphan*/  B2055_C2_TX_PGAPADTN ; 
 int /*<<< orphan*/  B2055_LGBUF_CENBUF ; 
 int /*<<< orphan*/  B2055_LGEN_TUNE1 ; 
 int /*<<< orphan*/  B2055_LGEN_TUNE2 ; 
 int /*<<< orphan*/  B2055_PLL_LFC1 ; 
 int /*<<< orphan*/  B2055_PLL_LFC2 ; 
 int /*<<< orphan*/  B2055_PLL_LFR1 ; 
 int /*<<< orphan*/  B2055_PLL_REF ; 
 int /*<<< orphan*/  B2055_RF_PLLMOD0 ; 
 int /*<<< orphan*/  B2055_RF_PLLMOD1 ; 
 int /*<<< orphan*/  B2055_VCO_CAL1 ; 
 int /*<<< orphan*/  B2055_VCO_CAL2 ; 
 int /*<<< orphan*/  B2055_VCO_CAPTAIL ; 
 int /*<<< orphan*/  B43_MMIO_MACCTL ; 
 int /*<<< orphan*/  b43_radio_write (struct b43_wldev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  b43_read32 (struct b43_wldev*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void b43_chantab_radio_upload(struct b43_wldev *dev,
				const struct b43_nphy_channeltab_entry_rev2 *e)
{
	b43_radio_write(dev, B2055_PLL_REF, e->radio_pll_ref);
	b43_radio_write(dev, B2055_RF_PLLMOD0, e->radio_rf_pllmod0);
	b43_radio_write(dev, B2055_RF_PLLMOD1, e->radio_rf_pllmod1);
	b43_radio_write(dev, B2055_VCO_CAPTAIL, e->radio_vco_captail);
	b43_read32(dev, B43_MMIO_MACCTL); /* flush writes */

	b43_radio_write(dev, B2055_VCO_CAL1, e->radio_vco_cal1);
	b43_radio_write(dev, B2055_VCO_CAL2, e->radio_vco_cal2);
	b43_radio_write(dev, B2055_PLL_LFC1, e->radio_pll_lfc1);
	b43_radio_write(dev, B2055_PLL_LFR1, e->radio_pll_lfr1);
	b43_read32(dev, B43_MMIO_MACCTL); /* flush writes */

	b43_radio_write(dev, B2055_PLL_LFC2, e->radio_pll_lfc2);
	b43_radio_write(dev, B2055_LGBUF_CENBUF, e->radio_lgbuf_cenbuf);
	b43_radio_write(dev, B2055_LGEN_TUNE1, e->radio_lgen_tune1);
	b43_radio_write(dev, B2055_LGEN_TUNE2, e->radio_lgen_tune2);
	b43_read32(dev, B43_MMIO_MACCTL); /* flush writes */

	b43_radio_write(dev, B2055_C1_LGBUF_ATUNE, e->radio_c1_lgbuf_atune);
	b43_radio_write(dev, B2055_C1_LGBUF_GTUNE, e->radio_c1_lgbuf_gtune);
	b43_radio_write(dev, B2055_C1_RX_RFR1, e->radio_c1_rx_rfr1);
	b43_radio_write(dev, B2055_C1_TX_PGAPADTN, e->radio_c1_tx_pgapadtn);
	b43_read32(dev, B43_MMIO_MACCTL); /* flush writes */

	b43_radio_write(dev, B2055_C1_TX_MXBGTRIM, e->radio_c1_tx_mxbgtrim);
	b43_radio_write(dev, B2055_C2_LGBUF_ATUNE, e->radio_c2_lgbuf_atune);
	b43_radio_write(dev, B2055_C2_LGBUF_GTUNE, e->radio_c2_lgbuf_gtune);
	b43_radio_write(dev, B2055_C2_RX_RFR1, e->radio_c2_rx_rfr1);
	b43_read32(dev, B43_MMIO_MACCTL); /* flush writes */

	b43_radio_write(dev, B2055_C2_TX_PGAPADTN, e->radio_c2_tx_pgapadtn);
	b43_radio_write(dev, B2055_C2_TX_MXBGTRIM, e->radio_c2_tx_mxbgtrim);
}