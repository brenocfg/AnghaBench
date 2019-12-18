#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
typedef  int u32 ;
typedef  scalar_t__ u16 ;
struct ieee80211_supported_band {int n_channels; TYPE_3__* channels; } ;
struct brcmu_chan {scalar_t__ band; scalar_t__ bw; scalar_t__ control_ch_num; scalar_t__ chspec; scalar_t__ chnum; int /*<<< orphan*/  sb; } ;
struct brcmf_pub {int dummy; } ;
struct brcmf_if {int dummy; } ;
struct brcmf_fil_bwcap_le {void* bw_cap; void* band; } ;
struct brcmf_chanspec_list {int /*<<< orphan*/ * element; int /*<<< orphan*/  count; } ;
struct TYPE_4__ {int /*<<< orphan*/  (* decchspec ) (struct brcmu_chan*) ;int /*<<< orphan*/  (* encchspec ) (struct brcmu_chan*) ;} ;
struct brcmf_cfg80211_info {TYPE_1__ d11inf; struct brcmf_pub* pub; } ;
typedef  int /*<<< orphan*/  band_bwcap ;
typedef  int /*<<< orphan*/  __le16 ;
struct TYPE_6__ {scalar_t__ hw_value; } ;
struct TYPE_5__ {struct ieee80211_supported_band** bands; } ;

/* Variables and functions */
 int /*<<< orphan*/  BRCMF_DCMD_MEDLEN ; 
 scalar_t__ BRCMU_CHAN_BAND_2G ; 
 scalar_t__ BRCMU_CHAN_BW_40 ; 
 int /*<<< orphan*/  BRCMU_CHAN_SB_NONE ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INFO ; 
 size_t NL80211_BAND_2GHZ ; 
 scalar_t__ WARN_ON (int) ; 
 int /*<<< orphan*/  WLC_BAND_2G ; 
 int WLC_BAND_5G ; 
 int /*<<< orphan*/  WLC_BW_CAP_40MHZ ; 
 int WLC_N_BW_40ALL ; 
 int /*<<< orphan*/  bphy_err (struct brcmf_pub*,char*,int) ; 
 int /*<<< orphan*/  brcmf_dbg (int /*<<< orphan*/ ,char*) ; 
 int brcmf_fil_iovar_data_get (struct brcmf_if*,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int brcmf_fil_iovar_data_set (struct brcmf_if*,char*,struct brcmf_fil_bwcap_le*,int) ; 
 int brcmf_fil_iovar_int_get (struct brcmf_if*,char*,int*) ; 
 int brcmf_fil_iovar_int_set (struct brcmf_if*,char*,int) ; 
 struct brcmf_if* brcmf_get_ifp (struct brcmf_pub*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  brcmf_update_bw40_channel_flag (TYPE_3__*,struct brcmu_chan*) ; 
 TYPE_2__* cfg_to_wiphy (struct brcmf_cfg80211_info*) ; 
 int /*<<< orphan*/  cpu_to_le16 (scalar_t__) ; 
 void* cpu_to_le32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * kzalloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int le32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct brcmu_chan*) ; 
 int /*<<< orphan*/  stub2 (struct brcmu_chan*) ; 

__attribute__((used)) static int brcmf_enable_bw40_2g(struct brcmf_cfg80211_info *cfg)
{
	struct brcmf_pub *drvr = cfg->pub;
	struct brcmf_if *ifp = brcmf_get_ifp(drvr, 0);
	struct ieee80211_supported_band *band;
	struct brcmf_fil_bwcap_le band_bwcap;
	struct brcmf_chanspec_list *list;
	u8 *pbuf;
	u32 val;
	int err;
	struct brcmu_chan ch;
	u32 num_chan;
	int i, j;

	/* verify support for bw_cap command */
	val = WLC_BAND_5G;
	err = brcmf_fil_iovar_int_get(ifp, "bw_cap", &val);

	if (!err) {
		/* only set 2G bandwidth using bw_cap command */
		band_bwcap.band = cpu_to_le32(WLC_BAND_2G);
		band_bwcap.bw_cap = cpu_to_le32(WLC_BW_CAP_40MHZ);
		err = brcmf_fil_iovar_data_set(ifp, "bw_cap", &band_bwcap,
					       sizeof(band_bwcap));
	} else {
		brcmf_dbg(INFO, "fallback to mimo_bw_cap\n");
		val = WLC_N_BW_40ALL;
		err = brcmf_fil_iovar_int_set(ifp, "mimo_bw_cap", val);
	}

	if (!err) {
		/* update channel info in 2G band */
		pbuf = kzalloc(BRCMF_DCMD_MEDLEN, GFP_KERNEL);

		if (pbuf == NULL)
			return -ENOMEM;

		ch.band = BRCMU_CHAN_BAND_2G;
		ch.bw = BRCMU_CHAN_BW_40;
		ch.sb = BRCMU_CHAN_SB_NONE;
		ch.chnum = 0;
		cfg->d11inf.encchspec(&ch);

		/* pass encoded chanspec in query */
		*(__le16 *)pbuf = cpu_to_le16(ch.chspec);

		err = brcmf_fil_iovar_data_get(ifp, "chanspecs", pbuf,
					       BRCMF_DCMD_MEDLEN);
		if (err) {
			bphy_err(drvr, "get chanspecs error (%d)\n", err);
			kfree(pbuf);
			return err;
		}

		band = cfg_to_wiphy(cfg)->bands[NL80211_BAND_2GHZ];
		list = (struct brcmf_chanspec_list *)pbuf;
		num_chan = le32_to_cpu(list->count);
		for (i = 0; i < num_chan; i++) {
			ch.chspec = (u16)le32_to_cpu(list->element[i]);
			cfg->d11inf.decchspec(&ch);
			if (WARN_ON(ch.band != BRCMU_CHAN_BAND_2G))
				continue;
			if (WARN_ON(ch.bw != BRCMU_CHAN_BW_40))
				continue;
			for (j = 0; j < band->n_channels; j++) {
				if (band->channels[j].hw_value == ch.control_ch_num)
					break;
			}
			if (WARN_ON(j == band->n_channels))
				continue;

			brcmf_update_bw40_channel_flag(&band->channels[j], &ch);
		}
		kfree(pbuf);
	}
	return err;
}