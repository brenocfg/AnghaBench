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
typedef  int u32 ;
typedef  int u16 ;
struct mt76x02_dev {int dummy; } ;

/* Variables and functions */
 int ARRAY_SIZE (int*) ; 
 int IEEE80211_HT_OP_MODE_NON_GF_STA_PRSNT ; 
 int IEEE80211_HT_OP_MODE_PROTECTION ; 
#define  IEEE80211_HT_OP_MODE_PROTECTION_20MHZ 130 
#define  IEEE80211_HT_OP_MODE_PROTECTION_NONHT_MIXED 129 
#define  IEEE80211_HT_OP_MODE_PROTECTION_NONMEMBER 128 
 scalar_t__ MT_CCK_PROT_CFG ; 
 int MT_PROT_CFG_CTRL ; 
 int MT_PROT_CFG_RATE ; 
 int MT_PROT_CTRL_CTS2SELF ; 
 int MT_PROT_CTRL_RTS_CTS ; 
 int MT_PROT_RATE_CCK_11 ; 
 int MT_PROT_RATE_DUP_OFDM_24 ; 
 int MT_PROT_RATE_OFDM_24 ; 
 int MT_PROT_RATE_SGI_OFDM_24 ; 
 scalar_t__ MT_TX_PROT_CFG6 ; 
 int /*<<< orphan*/  MT_TX_RTS_CFG ; 
 int /*<<< orphan*/  MT_TX_RTS_CFG_THRESH ; 
 int mt76_get_field (struct mt76x02_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int mt76_rr (struct mt76x02_dev*,scalar_t__) ; 
 int /*<<< orphan*/  mt76_wr (struct mt76x02_dev*,scalar_t__,int) ; 

void mt76x02_mac_set_tx_protection(struct mt76x02_dev *dev, bool legacy_prot,
				   int ht_mode)
{
	int mode = ht_mode & IEEE80211_HT_OP_MODE_PROTECTION;
	bool non_gf = !!(ht_mode & IEEE80211_HT_OP_MODE_NON_GF_STA_PRSNT);
	u32 prot[6];
	u32 vht_prot[3];
	int i;
	u16 rts_thr;

	for (i = 0; i < ARRAY_SIZE(prot); i++) {
		prot[i] = mt76_rr(dev, MT_CCK_PROT_CFG + i * 4);
		prot[i] &= ~MT_PROT_CFG_CTRL;
		if (i >= 2)
			prot[i] &= ~MT_PROT_CFG_RATE;
	}

	for (i = 0; i < ARRAY_SIZE(vht_prot); i++) {
		vht_prot[i] = mt76_rr(dev, MT_TX_PROT_CFG6 + i * 4);
		vht_prot[i] &= ~(MT_PROT_CFG_CTRL | MT_PROT_CFG_RATE);
	}

	rts_thr = mt76_get_field(dev, MT_TX_RTS_CFG, MT_TX_RTS_CFG_THRESH);

	if (rts_thr != 0xffff)
		prot[0] |= MT_PROT_CTRL_RTS_CTS;

	if (legacy_prot) {
		prot[1] |= MT_PROT_CTRL_CTS2SELF;

		prot[2] |= MT_PROT_RATE_CCK_11;
		prot[3] |= MT_PROT_RATE_CCK_11;
		prot[4] |= MT_PROT_RATE_CCK_11;
		prot[5] |= MT_PROT_RATE_CCK_11;

		vht_prot[0] |= MT_PROT_RATE_CCK_11;
		vht_prot[1] |= MT_PROT_RATE_CCK_11;
		vht_prot[2] |= MT_PROT_RATE_CCK_11;
	} else {
		if (rts_thr != 0xffff)
			prot[1] |= MT_PROT_CTRL_RTS_CTS;

		prot[2] |= MT_PROT_RATE_OFDM_24;
		prot[3] |= MT_PROT_RATE_DUP_OFDM_24;
		prot[4] |= MT_PROT_RATE_OFDM_24;
		prot[5] |= MT_PROT_RATE_DUP_OFDM_24;

		vht_prot[0] |= MT_PROT_RATE_OFDM_24;
		vht_prot[1] |= MT_PROT_RATE_DUP_OFDM_24;
		vht_prot[2] |= MT_PROT_RATE_SGI_OFDM_24;
	}

	switch (mode) {
	case IEEE80211_HT_OP_MODE_PROTECTION_NONMEMBER:
	case IEEE80211_HT_OP_MODE_PROTECTION_NONHT_MIXED:
		prot[2] |= MT_PROT_CTRL_RTS_CTS;
		prot[3] |= MT_PROT_CTRL_RTS_CTS;
		prot[4] |= MT_PROT_CTRL_RTS_CTS;
		prot[5] |= MT_PROT_CTRL_RTS_CTS;
		vht_prot[0] |= MT_PROT_CTRL_RTS_CTS;
		vht_prot[1] |= MT_PROT_CTRL_RTS_CTS;
		vht_prot[2] |= MT_PROT_CTRL_RTS_CTS;
		break;
	case IEEE80211_HT_OP_MODE_PROTECTION_20MHZ:
		prot[3] |= MT_PROT_CTRL_RTS_CTS;
		prot[5] |= MT_PROT_CTRL_RTS_CTS;
		vht_prot[1] |= MT_PROT_CTRL_RTS_CTS;
		vht_prot[2] |= MT_PROT_CTRL_RTS_CTS;
		break;
	}

	if (non_gf) {
		prot[4] |= MT_PROT_CTRL_RTS_CTS;
		prot[5] |= MT_PROT_CTRL_RTS_CTS;
	}

	for (i = 0; i < ARRAY_SIZE(prot); i++)
		mt76_wr(dev, MT_CCK_PROT_CFG + i * 4, prot[i]);

	for (i = 0; i < ARRAY_SIZE(vht_prot); i++)
		mt76_wr(dev, MT_TX_PROT_CFG6 + i * 4, vht_prot[i]);
}