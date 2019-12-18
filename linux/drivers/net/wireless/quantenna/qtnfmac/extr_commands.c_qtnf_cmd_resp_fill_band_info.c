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
struct qlink_tlv_hdr {scalar_t__ val; int /*<<< orphan*/  len; int /*<<< orphan*/  type; } ;
struct qlink_resp_band_info_get {int num_chans; scalar_t__ info; } ;
struct qlink_channel {int /*<<< orphan*/  dfs_state; int /*<<< orphan*/  dfs_cac_ms; int /*<<< orphan*/  beacon_found; scalar_t__ max_reg_power; scalar_t__ max_power; scalar_t__ max_antenna_gain; int /*<<< orphan*/  center_freq; int /*<<< orphan*/  hw_value; int /*<<< orphan*/  flags; } ;
struct ieee80211_vht_cap {int dummy; } ;
struct ieee80211_channel {int max_antenna_gain; int max_power; int max_reg_power; int /*<<< orphan*/  flags; void* hw_value; int /*<<< orphan*/  dfs_state; int /*<<< orphan*/  dfs_state_entered; void* dfs_cac_ms; int /*<<< orphan*/  beacon_found; void* center_freq; int /*<<< orphan*/  band; } ;
struct ieee80211_supported_band {int n_channels; struct ieee80211_channel* channels; struct ieee80211_channel vht_cap; struct ieee80211_channel ht_cap; int /*<<< orphan*/  band; } ;
struct ieee80211_ht_cap {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IEEE80211_CHAN_DISABLED ; 
 int /*<<< orphan*/  IEEE80211_CHAN_INDOOR_ONLY ; 
 int /*<<< orphan*/  IEEE80211_CHAN_IR_CONCURRENT ; 
 int /*<<< orphan*/  IEEE80211_CHAN_NO_10MHZ ; 
 int /*<<< orphan*/  IEEE80211_CHAN_NO_160MHZ ; 
 int /*<<< orphan*/  IEEE80211_CHAN_NO_20MHZ ; 
 int /*<<< orphan*/  IEEE80211_CHAN_NO_80MHZ ; 
 int /*<<< orphan*/  IEEE80211_CHAN_NO_HT40MINUS ; 
 int /*<<< orphan*/  IEEE80211_CHAN_NO_HT40PLUS ; 
 int /*<<< orphan*/  IEEE80211_CHAN_NO_IR ; 
 int /*<<< orphan*/  IEEE80211_CHAN_NO_OFDM ; 
 int /*<<< orphan*/  IEEE80211_CHAN_RADAR ; 
 int /*<<< orphan*/  NL80211_DFS_AVAILABLE ; 
 int /*<<< orphan*/  NL80211_DFS_UNAVAILABLE ; 
 int /*<<< orphan*/  NL80211_DFS_USABLE ; 
 int QLINK_CHAN_DISABLED ; 
 int QLINK_CHAN_INDOOR_ONLY ; 
 int QLINK_CHAN_IR_CONCURRENT ; 
 int QLINK_CHAN_NO_10MHZ ; 
 int QLINK_CHAN_NO_160MHZ ; 
 int QLINK_CHAN_NO_20MHZ ; 
 int QLINK_CHAN_NO_80MHZ ; 
 int QLINK_CHAN_NO_HT40MINUS ; 
 int QLINK_CHAN_NO_HT40PLUS ; 
 int QLINK_CHAN_NO_IR ; 
 int QLINK_CHAN_NO_OFDM ; 
 int QLINK_CHAN_RADAR ; 
 int /*<<< orphan*/  QLINK_DFS_AVAILABLE ; 
 int /*<<< orphan*/  QLINK_DFS_USABLE ; 
#define  QTN_TLV_ID_CHANNEL 130 
#define  WLAN_EID_HT_CAPABILITY 129 
#define  WLAN_EID_VHT_CAPABILITY 128 
 int /*<<< orphan*/  jiffies ; 
 struct ieee80211_channel* kcalloc (int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct ieee80211_channel*) ; 
 void* le16_to_cpu (int /*<<< orphan*/ ) ; 
 void* le32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct ieee80211_channel*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pr_debug (char*,void*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  pr_err (char*,...) ; 
 int /*<<< orphan*/  pr_warn (char*,int,...) ; 
 int /*<<< orphan*/  qtnf_cmd_resp_band_fill_htcap (scalar_t__,struct ieee80211_channel*) ; 
 int /*<<< orphan*/  qtnf_cmd_resp_band_fill_vhtcap (scalar_t__,struct ieee80211_channel*) ; 
 int /*<<< orphan*/  unlikely (int) ; 

__attribute__((used)) static int
qtnf_cmd_resp_fill_band_info(struct ieee80211_supported_band *band,
			     struct qlink_resp_band_info_get *resp,
			     size_t payload_len)
{
	u16 tlv_type;
	size_t tlv_len;
	size_t tlv_dlen;
	const struct qlink_tlv_hdr *tlv;
	const struct qlink_channel *qchan;
	struct ieee80211_channel *chan;
	unsigned int chidx = 0;
	u32 qflags;

	memset(&band->ht_cap, 0, sizeof(band->ht_cap));
	memset(&band->vht_cap, 0, sizeof(band->vht_cap));

	if (band->channels) {
		if (band->n_channels == resp->num_chans) {
			memset(band->channels, 0,
			       sizeof(*band->channels) * band->n_channels);
		} else {
			kfree(band->channels);
			band->n_channels = 0;
			band->channels = NULL;
		}
	}

	band->n_channels = resp->num_chans;
	if (band->n_channels == 0)
		return 0;

	if (!band->channels)
		band->channels = kcalloc(band->n_channels, sizeof(*chan),
					 GFP_KERNEL);
	if (!band->channels) {
		band->n_channels = 0;
		return -ENOMEM;
	}

	tlv = (struct qlink_tlv_hdr *)resp->info;

	while (payload_len >= sizeof(*tlv)) {
		tlv_type = le16_to_cpu(tlv->type);
		tlv_dlen = le16_to_cpu(tlv->len);
		tlv_len = tlv_dlen + sizeof(*tlv);

		if (tlv_len > payload_len) {
			pr_warn("malformed TLV 0x%.2X; LEN: %zu\n",
				tlv_type, tlv_len);
			goto error_ret;
		}

		switch (tlv_type) {
		case QTN_TLV_ID_CHANNEL:
			if (unlikely(tlv_dlen != sizeof(*qchan))) {
				pr_err("invalid channel TLV len %zu\n",
				       tlv_len);
				goto error_ret;
			}

			if (chidx == band->n_channels) {
				pr_err("too many channel TLVs\n");
				goto error_ret;
			}

			qchan = (const struct qlink_channel *)tlv->val;
			chan = &band->channels[chidx++];
			qflags = le32_to_cpu(qchan->flags);

			chan->hw_value = le16_to_cpu(qchan->hw_value);
			chan->band = band->band;
			chan->center_freq = le16_to_cpu(qchan->center_freq);
			chan->max_antenna_gain = (int)qchan->max_antenna_gain;
			chan->max_power = (int)qchan->max_power;
			chan->max_reg_power = (int)qchan->max_reg_power;
			chan->beacon_found = qchan->beacon_found;
			chan->dfs_cac_ms = le32_to_cpu(qchan->dfs_cac_ms);
			chan->flags = 0;

			if (qflags & QLINK_CHAN_DISABLED)
				chan->flags |= IEEE80211_CHAN_DISABLED;

			if (qflags & QLINK_CHAN_NO_IR)
				chan->flags |= IEEE80211_CHAN_NO_IR;

			if (qflags & QLINK_CHAN_NO_HT40PLUS)
				chan->flags |= IEEE80211_CHAN_NO_HT40PLUS;

			if (qflags & QLINK_CHAN_NO_HT40MINUS)
				chan->flags |= IEEE80211_CHAN_NO_HT40MINUS;

			if (qflags & QLINK_CHAN_NO_OFDM)
				chan->flags |= IEEE80211_CHAN_NO_OFDM;

			if (qflags & QLINK_CHAN_NO_80MHZ)
				chan->flags |= IEEE80211_CHAN_NO_80MHZ;

			if (qflags & QLINK_CHAN_NO_160MHZ)
				chan->flags |= IEEE80211_CHAN_NO_160MHZ;

			if (qflags & QLINK_CHAN_INDOOR_ONLY)
				chan->flags |= IEEE80211_CHAN_INDOOR_ONLY;

			if (qflags & QLINK_CHAN_IR_CONCURRENT)
				chan->flags |= IEEE80211_CHAN_IR_CONCURRENT;

			if (qflags & QLINK_CHAN_NO_20MHZ)
				chan->flags |= IEEE80211_CHAN_NO_20MHZ;

			if (qflags & QLINK_CHAN_NO_10MHZ)
				chan->flags |= IEEE80211_CHAN_NO_10MHZ;

			if (qflags & QLINK_CHAN_RADAR) {
				chan->flags |= IEEE80211_CHAN_RADAR;
				chan->dfs_state_entered = jiffies;

				if (qchan->dfs_state == QLINK_DFS_USABLE)
					chan->dfs_state = NL80211_DFS_USABLE;
				else if (qchan->dfs_state ==
					QLINK_DFS_AVAILABLE)
					chan->dfs_state = NL80211_DFS_AVAILABLE;
				else
					chan->dfs_state =
						NL80211_DFS_UNAVAILABLE;
			}

			pr_debug("chan=%d flags=%#x max_pow=%d max_reg_pow=%d\n",
				 chan->hw_value, chan->flags, chan->max_power,
				 chan->max_reg_power);
			break;
		case WLAN_EID_HT_CAPABILITY:
			if (unlikely(tlv_dlen !=
				     sizeof(struct ieee80211_ht_cap))) {
				pr_err("bad HTCAP TLV len %zu\n", tlv_dlen);
				goto error_ret;
			}

			qtnf_cmd_resp_band_fill_htcap(tlv->val, &band->ht_cap);
			break;
		case WLAN_EID_VHT_CAPABILITY:
			if (unlikely(tlv_dlen !=
				     sizeof(struct ieee80211_vht_cap))) {
				pr_err("bad VHTCAP TLV len %zu\n", tlv_dlen);
				goto error_ret;
			}

			qtnf_cmd_resp_band_fill_vhtcap(tlv->val,
						       &band->vht_cap);
			break;
		default:
			pr_warn("unknown TLV type: %#x\n", tlv_type);
			break;
		}

		payload_len -= tlv_len;
		tlv = (struct qlink_tlv_hdr *)(tlv->val + tlv_dlen);
	}

	if (payload_len) {
		pr_err("malformed TLV buf; bytes left: %zu\n", payload_len);
		goto error_ret;
	}

	if (band->n_channels != chidx) {
		pr_err("channel count mismatch: reported=%d, parsed=%d\n",
		       band->n_channels, chidx);
		goto error_ret;
	}

	return 0;

error_ret:
	kfree(band->channels);
	band->channels = NULL;
	band->n_channels = 0;

	return -EINVAL;
}