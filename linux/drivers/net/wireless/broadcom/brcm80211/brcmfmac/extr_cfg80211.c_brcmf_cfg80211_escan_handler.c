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
typedef  int u32 ;
struct brcmf_scan_results {size_t buflen; int count; int version; struct brcmf_bss_info_le* bss_info_le; } ;
struct brcmf_pub {struct brcmf_cfg80211_info* config; } ;
struct brcmf_if {int /*<<< orphan*/  bsscfgidx; struct brcmf_pub* drvr; } ;
struct brcmf_event_msg {scalar_t__ status; int datalen; } ;
struct brcmf_bss_info_le {int /*<<< orphan*/  version; int /*<<< orphan*/  length; int /*<<< orphan*/  capability; } ;
struct brcmf_escan_result_le {struct brcmf_bss_info_le bss_info_le; int /*<<< orphan*/  bss_count; int /*<<< orphan*/  buflen; } ;
struct TYPE_3__ {int /*<<< orphan*/  escan_state; int /*<<< orphan*/ * escan_buf; } ;
struct brcmf_cfg80211_info {scalar_t__ scan_request; scalar_t__ int_escan_map; TYPE_1__ escan_info; int /*<<< orphan*/  scan_status; } ;
typedef  scalar_t__ s32 ;
struct TYPE_4__ {int interface_modes; } ;

/* Variables and functions */
 int BIT (int /*<<< orphan*/ ) ; 
 int BRCMF_ESCAN_BUF_SIZE ; 
 scalar_t__ BRCMF_E_STATUS_ABORT ; 
 scalar_t__ BRCMF_E_STATUS_PARTIAL ; 
 scalar_t__ BRCMF_E_STATUS_SUCCESS ; 
 int /*<<< orphan*/  BRCMF_SCAN_STATUS_BUSY ; 
 scalar_t__ EPERM ; 
 int /*<<< orphan*/  NL80211_IFTYPE_ADHOC ; 
 int /*<<< orphan*/  SCAN ; 
 int WLAN_CAPABILITY_IBSS ; 
 int WL_ESCAN_RESULTS_FIXED_SIZE ; 
 int /*<<< orphan*/  WL_ESCAN_STATE_IDLE ; 
 int /*<<< orphan*/  bphy_err (struct brcmf_pub*,char*,...) ; 
 scalar_t__ brcmf_compare_update_same_bss (struct brcmf_cfg80211_info*,struct brcmf_bss_info_le*,struct brcmf_bss_info_le*) ; 
 int /*<<< orphan*/  brcmf_dbg (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  brcmf_inform_bss (struct brcmf_cfg80211_info*) ; 
 int /*<<< orphan*/  brcmf_notify_escan_complete (struct brcmf_cfg80211_info*,struct brcmf_if*,int,int) ; 
 scalar_t__ brcmf_p2p_scan_finding_common_channel (struct brcmf_cfg80211_info*,struct brcmf_bss_info_le*) ; 
 TYPE_2__* cfg_to_wiphy (struct brcmf_cfg80211_info*) ; 
 int le16_to_cpu (int /*<<< orphan*/ ) ; 
 int le32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,struct brcmf_bss_info_le*,int) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static s32
brcmf_cfg80211_escan_handler(struct brcmf_if *ifp,
			     const struct brcmf_event_msg *e, void *data)
{
	struct brcmf_pub *drvr = ifp->drvr;
	struct brcmf_cfg80211_info *cfg = drvr->config;
	s32 status;
	struct brcmf_escan_result_le *escan_result_le;
	u32 escan_buflen;
	struct brcmf_bss_info_le *bss_info_le;
	struct brcmf_bss_info_le *bss = NULL;
	u32 bi_length;
	struct brcmf_scan_results *list;
	u32 i;
	bool aborted;

	status = e->status;

	if (status == BRCMF_E_STATUS_ABORT)
		goto exit;

	if (!test_bit(BRCMF_SCAN_STATUS_BUSY, &cfg->scan_status)) {
		bphy_err(drvr, "scan not ready, bsscfgidx=%d\n",
			 ifp->bsscfgidx);
		return -EPERM;
	}

	if (status == BRCMF_E_STATUS_PARTIAL) {
		brcmf_dbg(SCAN, "ESCAN Partial result\n");
		if (e->datalen < sizeof(*escan_result_le)) {
			bphy_err(drvr, "invalid event data length\n");
			goto exit;
		}
		escan_result_le = (struct brcmf_escan_result_le *) data;
		if (!escan_result_le) {
			bphy_err(drvr, "Invalid escan result (NULL pointer)\n");
			goto exit;
		}
		escan_buflen = le32_to_cpu(escan_result_le->buflen);
		if (escan_buflen > BRCMF_ESCAN_BUF_SIZE ||
		    escan_buflen > e->datalen ||
		    escan_buflen < sizeof(*escan_result_le)) {
			bphy_err(drvr, "Invalid escan buffer length: %d\n",
				 escan_buflen);
			goto exit;
		}
		if (le16_to_cpu(escan_result_le->bss_count) != 1) {
			bphy_err(drvr, "Invalid bss_count %d: ignoring\n",
				 escan_result_le->bss_count);
			goto exit;
		}
		bss_info_le = &escan_result_le->bss_info_le;

		if (brcmf_p2p_scan_finding_common_channel(cfg, bss_info_le))
			goto exit;

		if (!cfg->int_escan_map && !cfg->scan_request) {
			brcmf_dbg(SCAN, "result without cfg80211 request\n");
			goto exit;
		}

		bi_length = le32_to_cpu(bss_info_le->length);
		if (bi_length != escan_buflen -	WL_ESCAN_RESULTS_FIXED_SIZE) {
			bphy_err(drvr, "Ignoring invalid bss_info length: %d\n",
				 bi_length);
			goto exit;
		}

		if (!(cfg_to_wiphy(cfg)->interface_modes &
					BIT(NL80211_IFTYPE_ADHOC))) {
			if (le16_to_cpu(bss_info_le->capability) &
						WLAN_CAPABILITY_IBSS) {
				bphy_err(drvr, "Ignoring IBSS result\n");
				goto exit;
			}
		}

		list = (struct brcmf_scan_results *)
				cfg->escan_info.escan_buf;
		if (bi_length > BRCMF_ESCAN_BUF_SIZE - list->buflen) {
			bphy_err(drvr, "Buffer is too small: ignoring\n");
			goto exit;
		}

		for (i = 0; i < list->count; i++) {
			bss = bss ? (struct brcmf_bss_info_le *)
				((unsigned char *)bss +
				le32_to_cpu(bss->length)) : list->bss_info_le;
			if (brcmf_compare_update_same_bss(cfg, bss,
							  bss_info_le))
				goto exit;
		}
		memcpy(&cfg->escan_info.escan_buf[list->buflen], bss_info_le,
		       bi_length);
		list->version = le32_to_cpu(bss_info_le->version);
		list->buflen += bi_length;
		list->count++;
	} else {
		cfg->escan_info.escan_state = WL_ESCAN_STATE_IDLE;
		if (brcmf_p2p_scan_finding_common_channel(cfg, NULL))
			goto exit;
		if (cfg->int_escan_map || cfg->scan_request) {
			brcmf_inform_bss(cfg);
			aborted = status != BRCMF_E_STATUS_SUCCESS;
			brcmf_notify_escan_complete(cfg, ifp, aborted, false);
		} else
			brcmf_dbg(SCAN, "Ignored scan complete result 0x%x\n",
				  status);
	}
exit:
	return 0;
}