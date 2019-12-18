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
typedef  int u64 ;
typedef  int u32 ;
struct tg3 {int dma_limit; int phy_flags; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 scalar_t__ ASIC_REV_5780 ; 
 int /*<<< orphan*/  CPMU_PRESENT ; 
 int EIO ; 
 int /*<<< orphan*/  ENABLE_RSS ; 
 int ETH_FRAME_LEN ; 
 int ETH_HLEN ; 
 int /*<<< orphan*/  JUMBO_RING_ENABLE ; 
 int MAC_RSS_INDIR_TBL_0 ; 
 int /*<<< orphan*/  MAC_TX_STATUS ; 
 size_t TG3_EXT_LOOPB_TEST ; 
 int TG3_JMB_LOOPBACK_FAILED ; 
 int TG3_LOOPBACK_FAILED ; 
 size_t TG3_MAC_LOOPB_TEST ; 
 int TG3_PHYFLG_EEE_CAP ; 
 int TG3_PHYFLG_ENABLE_APD ; 
 int TG3_PHYFLG_PHY_SERDES ; 
 size_t TG3_PHY_LOOPB_TEST ; 
 int TG3_RSS_INDIR_TBL_SIZE ; 
 int TG3_STD_LOOPBACK_FAILED ; 
 int TG3_TSO_LOOPBACK_FAILED ; 
 int /*<<< orphan*/  TSO_CAPABLE ; 
 int TX_STATUS_LINK_UP ; 
 int /*<<< orphan*/  USE_PHYLIB ; 
 int /*<<< orphan*/  mdelay (int) ; 
 int /*<<< orphan*/  netif_running (int /*<<< orphan*/ ) ; 
 scalar_t__ tg3_asic_rev (struct tg3*) ; 
 scalar_t__ tg3_flag (struct tg3*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tg3_mac_loopback (struct tg3*,int) ; 
 int /*<<< orphan*/  tg3_phy_lpbk_set (struct tg3*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  tg3_phy_toggle_apd (struct tg3*,int) ; 
 int tg3_reset_hw (struct tg3*,int) ; 
 scalar_t__ tg3_run_loopback (struct tg3*,int,int) ; 
 int tr32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tw32 (int,int) ; 

__attribute__((used)) static int tg3_test_loopback(struct tg3 *tp, u64 *data, bool do_extlpbk)
{
	int err = -EIO;
	u32 eee_cap;
	u32 jmb_pkt_sz = 9000;

	if (tp->dma_limit)
		jmb_pkt_sz = tp->dma_limit - ETH_HLEN;

	eee_cap = tp->phy_flags & TG3_PHYFLG_EEE_CAP;
	tp->phy_flags &= ~TG3_PHYFLG_EEE_CAP;

	if (!netif_running(tp->dev)) {
		data[TG3_MAC_LOOPB_TEST] = TG3_LOOPBACK_FAILED;
		data[TG3_PHY_LOOPB_TEST] = TG3_LOOPBACK_FAILED;
		if (do_extlpbk)
			data[TG3_EXT_LOOPB_TEST] = TG3_LOOPBACK_FAILED;
		goto done;
	}

	err = tg3_reset_hw(tp, true);
	if (err) {
		data[TG3_MAC_LOOPB_TEST] = TG3_LOOPBACK_FAILED;
		data[TG3_PHY_LOOPB_TEST] = TG3_LOOPBACK_FAILED;
		if (do_extlpbk)
			data[TG3_EXT_LOOPB_TEST] = TG3_LOOPBACK_FAILED;
		goto done;
	}

	if (tg3_flag(tp, ENABLE_RSS)) {
		int i;

		/* Reroute all rx packets to the 1st queue */
		for (i = MAC_RSS_INDIR_TBL_0;
		     i < MAC_RSS_INDIR_TBL_0 + TG3_RSS_INDIR_TBL_SIZE; i += 4)
			tw32(i, 0x0);
	}

	/* HW errata - mac loopback fails in some cases on 5780.
	 * Normal traffic and PHY loopback are not affected by
	 * errata.  Also, the MAC loopback test is deprecated for
	 * all newer ASIC revisions.
	 */
	if (tg3_asic_rev(tp) != ASIC_REV_5780 &&
	    !tg3_flag(tp, CPMU_PRESENT)) {
		tg3_mac_loopback(tp, true);

		if (tg3_run_loopback(tp, ETH_FRAME_LEN, false))
			data[TG3_MAC_LOOPB_TEST] |= TG3_STD_LOOPBACK_FAILED;

		if (tg3_flag(tp, JUMBO_RING_ENABLE) &&
		    tg3_run_loopback(tp, jmb_pkt_sz + ETH_HLEN, false))
			data[TG3_MAC_LOOPB_TEST] |= TG3_JMB_LOOPBACK_FAILED;

		tg3_mac_loopback(tp, false);
	}

	if (!(tp->phy_flags & TG3_PHYFLG_PHY_SERDES) &&
	    !tg3_flag(tp, USE_PHYLIB)) {
		int i;

		tg3_phy_lpbk_set(tp, 0, false);

		/* Wait for link */
		for (i = 0; i < 100; i++) {
			if (tr32(MAC_TX_STATUS) & TX_STATUS_LINK_UP)
				break;
			mdelay(1);
		}

		if (tg3_run_loopback(tp, ETH_FRAME_LEN, false))
			data[TG3_PHY_LOOPB_TEST] |= TG3_STD_LOOPBACK_FAILED;
		if (tg3_flag(tp, TSO_CAPABLE) &&
		    tg3_run_loopback(tp, ETH_FRAME_LEN, true))
			data[TG3_PHY_LOOPB_TEST] |= TG3_TSO_LOOPBACK_FAILED;
		if (tg3_flag(tp, JUMBO_RING_ENABLE) &&
		    tg3_run_loopback(tp, jmb_pkt_sz + ETH_HLEN, false))
			data[TG3_PHY_LOOPB_TEST] |= TG3_JMB_LOOPBACK_FAILED;

		if (do_extlpbk) {
			tg3_phy_lpbk_set(tp, 0, true);

			/* All link indications report up, but the hardware
			 * isn't really ready for about 20 msec.  Double it
			 * to be sure.
			 */
			mdelay(40);

			if (tg3_run_loopback(tp, ETH_FRAME_LEN, false))
				data[TG3_EXT_LOOPB_TEST] |=
							TG3_STD_LOOPBACK_FAILED;
			if (tg3_flag(tp, TSO_CAPABLE) &&
			    tg3_run_loopback(tp, ETH_FRAME_LEN, true))
				data[TG3_EXT_LOOPB_TEST] |=
							TG3_TSO_LOOPBACK_FAILED;
			if (tg3_flag(tp, JUMBO_RING_ENABLE) &&
			    tg3_run_loopback(tp, jmb_pkt_sz + ETH_HLEN, false))
				data[TG3_EXT_LOOPB_TEST] |=
							TG3_JMB_LOOPBACK_FAILED;
		}

		/* Re-enable gphy autopowerdown. */
		if (tp->phy_flags & TG3_PHYFLG_ENABLE_APD)
			tg3_phy_toggle_apd(tp, true);
	}

	err = (data[TG3_MAC_LOOPB_TEST] | data[TG3_PHY_LOOPB_TEST] |
	       data[TG3_EXT_LOOPB_TEST]) ? -EIO : 0;

done:
	tp->phy_flags |= eee_cap;

	return err;
}