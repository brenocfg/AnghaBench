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
struct b43_nphy_channeltab_entry_rev3 {int /*<<< orphan*/  radio_tx1_mixg_boost_tune; int /*<<< orphan*/  radio_tx1_mixa_boost_tune; int /*<<< orphan*/  radio_tx1_pgag_boost_tune; int /*<<< orphan*/  radio_tx1_pgaa_boost_tune; int /*<<< orphan*/  radio_tx1_padg_boost_tune; int /*<<< orphan*/  radio_tx1_pada_boost_tune; int /*<<< orphan*/  radio_tx1_intpag_boost_tune; int /*<<< orphan*/  radio_tx1_intpaa_boost_tune; int /*<<< orphan*/  radio_rx1_lnag_tune; int /*<<< orphan*/  radio_rx1_lnaa_tune; int /*<<< orphan*/  radio_tx0_mixg_boost_tune; int /*<<< orphan*/  radio_tx0_mixa_boost_tune; int /*<<< orphan*/  radio_tx0_pgag_boost_tune; int /*<<< orphan*/  radio_tx0_pgaa_boost_tune; int /*<<< orphan*/  radio_tx0_padg_boost_tune; int /*<<< orphan*/  radio_tx0_pada_boost_tune; int /*<<< orphan*/  radio_tx0_intpag_boost_tune; int /*<<< orphan*/  radio_tx0_intpaa_boost_tune; int /*<<< orphan*/  radio_rx0_lnag_tune; int /*<<< orphan*/  radio_rx0_lnaa_tune; int /*<<< orphan*/  radio_syn_logen_buf4; int /*<<< orphan*/  radio_syn_logen_buf3; int /*<<< orphan*/  radio_syn_logen_mixer2; int /*<<< orphan*/  radio_syn_logen_vcobuf1; int /*<<< orphan*/  radio_syn_reserved_addr29; int /*<<< orphan*/  radio_syn_reserved_addr28; int /*<<< orphan*/  radio_syn_reserved_addr27; int /*<<< orphan*/  radio_syn_pll_loopfilter5; int /*<<< orphan*/  radio_syn_pll_loopfilter4; int /*<<< orphan*/  radio_syn_pll_loopfilter3; int /*<<< orphan*/  radio_syn_pll_loopfilter2; int /*<<< orphan*/  radio_syn_pll_loopfilter1; int /*<<< orphan*/  radio_syn_pll_mmd1; int /*<<< orphan*/  radio_syn_pll_mmd2; int /*<<< orphan*/  radio_syn_pll_refdiv; int /*<<< orphan*/  radio_syn_pll_vcocal2; int /*<<< orphan*/  radio_syn_pll_vcocal1; } ;

/* Variables and functions */
 int B2056_RX0 ; 
 int B2056_RX1 ; 
 int B2056_RX_LNAA_TUNE ; 
 int B2056_RX_LNAG_TUNE ; 
 int B2056_SYN_LOGEN_BUF3 ; 
 int B2056_SYN_LOGEN_BUF4 ; 
 int B2056_SYN_LOGEN_MIXER2 ; 
 int B2056_SYN_LOGEN_VCOBUF1 ; 
 int B2056_SYN_PLL_LOOPFILTER1 ; 
 int B2056_SYN_PLL_LOOPFILTER2 ; 
 int B2056_SYN_PLL_LOOPFILTER3 ; 
 int B2056_SYN_PLL_LOOPFILTER4 ; 
 int B2056_SYN_PLL_LOOPFILTER5 ; 
 int B2056_SYN_PLL_MMD1 ; 
 int B2056_SYN_PLL_MMD2 ; 
 int B2056_SYN_PLL_REFDIV ; 
 int B2056_SYN_PLL_VCOCAL1 ; 
 int B2056_SYN_PLL_VCOCAL2 ; 
 int B2056_SYN_RESERVED_ADDR27 ; 
 int B2056_SYN_RESERVED_ADDR28 ; 
 int B2056_SYN_RESERVED_ADDR29 ; 
 int B2056_TX0 ; 
 int B2056_TX1 ; 
 int B2056_TX_INTPAA_BOOST_TUNE ; 
 int B2056_TX_INTPAG_BOOST_TUNE ; 
 int B2056_TX_MIXA_BOOST_TUNE ; 
 int B2056_TX_MIXG_BOOST_TUNE ; 
 int B2056_TX_PADA_BOOST_TUNE ; 
 int B2056_TX_PADG_BOOST_TUNE ; 
 int B2056_TX_PGAA_BOOST_TUNE ; 
 int B2056_TX_PGAG_BOOST_TUNE ; 
 int /*<<< orphan*/  b43_radio_write (struct b43_wldev*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void b43_chantab_radio_2056_upload(struct b43_wldev *dev,
				const struct b43_nphy_channeltab_entry_rev3 *e)
{
	b43_radio_write(dev, B2056_SYN_PLL_VCOCAL1, e->radio_syn_pll_vcocal1);
	b43_radio_write(dev, B2056_SYN_PLL_VCOCAL2, e->radio_syn_pll_vcocal2);
	b43_radio_write(dev, B2056_SYN_PLL_REFDIV, e->radio_syn_pll_refdiv);
	b43_radio_write(dev, B2056_SYN_PLL_MMD2, e->radio_syn_pll_mmd2);
	b43_radio_write(dev, B2056_SYN_PLL_MMD1, e->radio_syn_pll_mmd1);
	b43_radio_write(dev, B2056_SYN_PLL_LOOPFILTER1,
					e->radio_syn_pll_loopfilter1);
	b43_radio_write(dev, B2056_SYN_PLL_LOOPFILTER2,
					e->radio_syn_pll_loopfilter2);
	b43_radio_write(dev, B2056_SYN_PLL_LOOPFILTER3,
					e->radio_syn_pll_loopfilter3);
	b43_radio_write(dev, B2056_SYN_PLL_LOOPFILTER4,
					e->radio_syn_pll_loopfilter4);
	b43_radio_write(dev, B2056_SYN_PLL_LOOPFILTER5,
					e->radio_syn_pll_loopfilter5);
	b43_radio_write(dev, B2056_SYN_RESERVED_ADDR27,
					e->radio_syn_reserved_addr27);
	b43_radio_write(dev, B2056_SYN_RESERVED_ADDR28,
					e->radio_syn_reserved_addr28);
	b43_radio_write(dev, B2056_SYN_RESERVED_ADDR29,
					e->radio_syn_reserved_addr29);
	b43_radio_write(dev, B2056_SYN_LOGEN_VCOBUF1,
					e->radio_syn_logen_vcobuf1);
	b43_radio_write(dev, B2056_SYN_LOGEN_MIXER2, e->radio_syn_logen_mixer2);
	b43_radio_write(dev, B2056_SYN_LOGEN_BUF3, e->radio_syn_logen_buf3);
	b43_radio_write(dev, B2056_SYN_LOGEN_BUF4, e->radio_syn_logen_buf4);

	b43_radio_write(dev, B2056_RX0 | B2056_RX_LNAA_TUNE,
					e->radio_rx0_lnaa_tune);
	b43_radio_write(dev, B2056_RX0 | B2056_RX_LNAG_TUNE,
					e->radio_rx0_lnag_tune);

	b43_radio_write(dev, B2056_TX0 | B2056_TX_INTPAA_BOOST_TUNE,
					e->radio_tx0_intpaa_boost_tune);
	b43_radio_write(dev, B2056_TX0 | B2056_TX_INTPAG_BOOST_TUNE,
					e->radio_tx0_intpag_boost_tune);
	b43_radio_write(dev, B2056_TX0 | B2056_TX_PADA_BOOST_TUNE,
					e->radio_tx0_pada_boost_tune);
	b43_radio_write(dev, B2056_TX0 | B2056_TX_PADG_BOOST_TUNE,
					e->radio_tx0_padg_boost_tune);
	b43_radio_write(dev, B2056_TX0 | B2056_TX_PGAA_BOOST_TUNE,
					e->radio_tx0_pgaa_boost_tune);
	b43_radio_write(dev, B2056_TX0 | B2056_TX_PGAG_BOOST_TUNE,
					e->radio_tx0_pgag_boost_tune);
	b43_radio_write(dev, B2056_TX0 | B2056_TX_MIXA_BOOST_TUNE,
					e->radio_tx0_mixa_boost_tune);
	b43_radio_write(dev, B2056_TX0 | B2056_TX_MIXG_BOOST_TUNE,
					e->radio_tx0_mixg_boost_tune);

	b43_radio_write(dev, B2056_RX1 | B2056_RX_LNAA_TUNE,
					e->radio_rx1_lnaa_tune);
	b43_radio_write(dev, B2056_RX1 | B2056_RX_LNAG_TUNE,
					e->radio_rx1_lnag_tune);

	b43_radio_write(dev, B2056_TX1 | B2056_TX_INTPAA_BOOST_TUNE,
					e->radio_tx1_intpaa_boost_tune);
	b43_radio_write(dev, B2056_TX1 | B2056_TX_INTPAG_BOOST_TUNE,
					e->radio_tx1_intpag_boost_tune);
	b43_radio_write(dev, B2056_TX1 | B2056_TX_PADA_BOOST_TUNE,
					e->radio_tx1_pada_boost_tune);
	b43_radio_write(dev, B2056_TX1 | B2056_TX_PADG_BOOST_TUNE,
					e->radio_tx1_padg_boost_tune);
	b43_radio_write(dev, B2056_TX1 | B2056_TX_PGAA_BOOST_TUNE,
					e->radio_tx1_pgaa_boost_tune);
	b43_radio_write(dev, B2056_TX1 | B2056_TX_PGAG_BOOST_TUNE,
					e->radio_tx1_pgag_boost_tune);
	b43_radio_write(dev, B2056_TX1 | B2056_TX_MIXA_BOOST_TUNE,
					e->radio_tx1_mixa_boost_tune);
	b43_radio_write(dev, B2056_TX1 | B2056_TX_MIXG_BOOST_TUNE,
					e->radio_tx1_mixg_boost_tune);
}