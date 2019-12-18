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
typedef  int /*<<< orphan*/  u8 ;
typedef  int u16 ;
struct wil_eapol_key {scalar_t__ type; int /*<<< orphan*/  key_info; } ;
struct wil_1x_hdr {scalar_t__ type; } ;
struct wil6210_priv {int dummy; } ;
struct sk_buff {int len; } ;
struct ethhdr {int dummy; } ;

/* Variables and functions */
 scalar_t__ WIL_1X_TYPE_EAPOL_KEY ; 
 scalar_t__ WIL_EAPOL_KEY_TYPE_RSN ; 
 scalar_t__ WIL_EAPOL_KEY_TYPE_WPA ; 
 int WIL_KEY_INFO_KEY_TYPE ; 
 int be16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * skb_mac_header (struct sk_buff*) ; 
 int /*<<< orphan*/  skb_mac_header_was_set (struct sk_buff*) ; 
 scalar_t__ skb_mac_offset (struct sk_buff*) ; 
 int /*<<< orphan*/  wil_err (struct wil6210_priv*,char*) ; 

__attribute__((used)) static struct wil_eapol_key *wil_is_ptk_eapol_key(struct wil6210_priv *wil,
						  struct sk_buff *skb)
{
	u8 *buf;
	const struct wil_1x_hdr *hdr;
	struct wil_eapol_key *key;
	u16 key_info;
	int len = skb->len;

	if (!skb_mac_header_was_set(skb)) {
		wil_err(wil, "mac header was not set\n");
		return NULL;
	}

	len -= skb_mac_offset(skb);

	if (len < sizeof(struct ethhdr) + sizeof(struct wil_1x_hdr) +
	    sizeof(struct wil_eapol_key))
		return NULL;

	buf = skb_mac_header(skb) + sizeof(struct ethhdr);

	hdr = (const struct wil_1x_hdr *)buf;
	if (hdr->type != WIL_1X_TYPE_EAPOL_KEY)
		return NULL;

	key = (struct wil_eapol_key *)(buf + sizeof(struct wil_1x_hdr));
	if (key->type != WIL_EAPOL_KEY_TYPE_WPA &&
	    key->type != WIL_EAPOL_KEY_TYPE_RSN)
		return NULL;

	key_info = be16_to_cpu(key->key_info);
	if (!(key_info & WIL_KEY_INFO_KEY_TYPE)) /* check if pairwise */
		return NULL;

	return key;
}