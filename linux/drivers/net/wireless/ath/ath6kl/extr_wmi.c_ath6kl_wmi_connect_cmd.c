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
typedef  void* u8 ;
typedef  int /*<<< orphan*/  u32 ;
typedef  int /*<<< orphan*/  u16 ;
struct wmi_connect_cmd {int ssid_len; int nw_type; int dot11_auth_mode; int auth_mode; int prwise_crypto_type; int grp_crypto_type; int /*<<< orphan*/  bssid; void* nw_subtype; int /*<<< orphan*/  ctrl_flags; int /*<<< orphan*/  ch; void* grp_crypto_len; void* prwise_crypto_len; int /*<<< orphan*/  ssid; } ;
struct wmi {int traffic_class; } ;
struct sk_buff {scalar_t__ data; } ;
typedef  enum network_type { ____Placeholder_network_type } network_type ;
typedef  enum dot11_auth_mode { ____Placeholder_dot11_auth_mode } dot11_auth_mode ;
typedef  enum auth_mode { ____Placeholder_auth_mode } auth_mode ;
typedef  enum ath6kl_crypto_type { ____Placeholder_ath6kl_crypto_type } ath6kl_crypto_type ;

/* Variables and functions */
 int /*<<< orphan*/  ATH6KL_DBG_WMI ; 
 int EINVAL ; 
 int ENOMEM ; 
 int ETH_ALEN ; 
 int NONE_CRYPT ; 
 int /*<<< orphan*/  NO_SYNC_WMIFLAG ; 
 int /*<<< orphan*/  WMI_CONNECT_CMDID ; 
 int /*<<< orphan*/  ath6kl_dbg (int /*<<< orphan*/ ,char*,void**,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int,int,int,int) ; 
 int /*<<< orphan*/  ath6kl_dbg_dump (int /*<<< orphan*/ ,int /*<<< orphan*/ *,char*,void**,int) ; 
 int ath6kl_wmi_cmd_send (struct wmi*,void*,struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct sk_buff* ath6kl_wmi_get_new_buf (int) ; 
 int /*<<< orphan*/  cpu_to_le16 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpu_to_le32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,void**,int) ; 

int ath6kl_wmi_connect_cmd(struct wmi *wmi, u8 if_idx,
			   enum network_type nw_type,
			   enum dot11_auth_mode dot11_auth_mode,
			   enum auth_mode auth_mode,
			   enum ath6kl_crypto_type pairwise_crypto,
			   u8 pairwise_crypto_len,
			   enum ath6kl_crypto_type group_crypto,
			   u8 group_crypto_len, int ssid_len, u8 *ssid,
			   u8 *bssid, u16 channel, u32 ctrl_flags,
			   u8 nw_subtype)
{
	struct sk_buff *skb;
	struct wmi_connect_cmd *cc;
	int ret;

	ath6kl_dbg(ATH6KL_DBG_WMI,
		   "wmi connect bssid %pM freq %d flags 0x%x ssid_len %d "
		   "type %d dot11_auth %d auth %d pairwise %d group %d\n",
		   bssid, channel, ctrl_flags, ssid_len, nw_type,
		   dot11_auth_mode, auth_mode, pairwise_crypto, group_crypto);
	ath6kl_dbg_dump(ATH6KL_DBG_WMI, NULL, "ssid ", ssid, ssid_len);

	wmi->traffic_class = 100;

	if ((pairwise_crypto == NONE_CRYPT) && (group_crypto != NONE_CRYPT))
		return -EINVAL;

	if ((pairwise_crypto != NONE_CRYPT) && (group_crypto == NONE_CRYPT))
		return -EINVAL;

	skb = ath6kl_wmi_get_new_buf(sizeof(struct wmi_connect_cmd));
	if (!skb)
		return -ENOMEM;

	cc = (struct wmi_connect_cmd *) skb->data;

	if (ssid_len)
		memcpy(cc->ssid, ssid, ssid_len);

	cc->ssid_len = ssid_len;
	cc->nw_type = nw_type;
	cc->dot11_auth_mode = dot11_auth_mode;
	cc->auth_mode = auth_mode;
	cc->prwise_crypto_type = pairwise_crypto;
	cc->prwise_crypto_len = pairwise_crypto_len;
	cc->grp_crypto_type = group_crypto;
	cc->grp_crypto_len = group_crypto_len;
	cc->ch = cpu_to_le16(channel);
	cc->ctrl_flags = cpu_to_le32(ctrl_flags);
	cc->nw_subtype = nw_subtype;

	if (bssid != NULL)
		memcpy(cc->bssid, bssid, ETH_ALEN);

	ret = ath6kl_wmi_cmd_send(wmi, if_idx, skb, WMI_CONNECT_CMDID,
				  NO_SYNC_WMIFLAG);

	return ret;
}