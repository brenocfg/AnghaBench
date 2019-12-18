#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
typedef  int u32 ;
typedef  int /*<<< orphan*/  u16 ;
struct sk_buff {int dummy; } ;
struct mt7601u_rxwi {int rxinfo; int /*<<< orphan*/  rate; int /*<<< orphan*/  ctl; } ;
struct TYPE_4__ {TYPE_1__* chan; } ;
struct mt7601u_dev {int /*<<< orphan*/  con_mon_lock; int /*<<< orphan*/  avg_rssi; TYPE_2__ chandef; } ;
struct ieee80211_rx_status {int* chain_signal; int signal; int /*<<< orphan*/  band; int /*<<< orphan*/  freq; int /*<<< orphan*/  chains; int /*<<< orphan*/  flag; } ;
struct TYPE_3__ {int /*<<< orphan*/  band; int /*<<< orphan*/  center_freq; } ;

/* Variables and functions */
 int /*<<< orphan*/  BIT (int /*<<< orphan*/ ) ; 
 int FIELD_GET (int /*<<< orphan*/ ,int) ; 
 struct ieee80211_rx_status* IEEE80211_SKB_RXCB (struct sk_buff*) ; 
 int /*<<< orphan*/  MT_RXINFO_DECRYPT ; 
 int /*<<< orphan*/  MT_RXINFO_PN_LEN ; 
 int /*<<< orphan*/  MT_RXINFO_U2M ; 
 int /*<<< orphan*/  MT_RXWI_CTL_MPDU_LEN ; 
 int /*<<< orphan*/  RX_FLAG_DECRYPTED ; 
 int /*<<< orphan*/  RX_FLAG_ICV_STRIPPED ; 
 int /*<<< orphan*/  RX_FLAG_IV_STRIPPED ; 
 int /*<<< orphan*/  RX_FLAG_MIC_STRIPPED ; 
 int /*<<< orphan*/  RX_FLAG_MMIC_STRIPPED ; 
 int cpu_to_le32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ewma_rssi_add (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  le16_to_cpu (int /*<<< orphan*/ ) ; 
 int le32_to_cpu (int /*<<< orphan*/ ) ; 
 int mt7601u_phy_get_rssi (struct mt7601u_dev*,struct mt7601u_rxwi*,int /*<<< orphan*/ ) ; 
 scalar_t__ mt7601u_rx_is_our_beacon (struct mt7601u_dev*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mt7601u_rx_monitor_beacon (struct mt7601u_dev*,struct mt7601u_rxwi*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mt76_mac_process_rate (struct ieee80211_rx_status*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 

u32 mt76_mac_process_rx(struct mt7601u_dev *dev, struct sk_buff *skb,
			u8 *data, void *rxi)
{
	struct ieee80211_rx_status *status = IEEE80211_SKB_RXCB(skb);
	struct mt7601u_rxwi *rxwi = rxi;
	u32 len, ctl = le32_to_cpu(rxwi->ctl);
	u16 rate = le16_to_cpu(rxwi->rate);
	int rssi;

	len = FIELD_GET(MT_RXWI_CTL_MPDU_LEN, ctl);
	if (len < 10)
		return 0;

	if (rxwi->rxinfo & cpu_to_le32(MT_RXINFO_DECRYPT)) {
		status->flag |= RX_FLAG_DECRYPTED;
		status->flag |= RX_FLAG_MMIC_STRIPPED;
		status->flag |= RX_FLAG_MIC_STRIPPED;
		status->flag |= RX_FLAG_ICV_STRIPPED;
		status->flag |= RX_FLAG_IV_STRIPPED;
	}
	/* let mac80211 take care of PN validation since apparently
	 * the hardware does not support it
	 */
	if (rxwi->rxinfo & cpu_to_le32(MT_RXINFO_PN_LEN))
		status->flag &= ~RX_FLAG_IV_STRIPPED;

	status->chains = BIT(0);
	rssi = mt7601u_phy_get_rssi(dev, rxwi, rate);
	status->chain_signal[0] = status->signal = rssi;
	status->freq = dev->chandef.chan->center_freq;
	status->band = dev->chandef.chan->band;

	mt76_mac_process_rate(status, rate);

	spin_lock_bh(&dev->con_mon_lock);
	if (mt7601u_rx_is_our_beacon(dev, data))
		mt7601u_rx_monitor_beacon(dev, rxwi, rate, rssi);
	else if (rxwi->rxinfo & cpu_to_le32(MT_RXINFO_U2M))
		ewma_rssi_add(&dev->avg_rssi, -rssi);
	spin_unlock_bh(&dev->con_mon_lock);

	return len;
}