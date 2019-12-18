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
typedef  unsigned int u8 ;
typedef  unsigned int u16 ;
struct sk_buff {int dummy; } ;
struct napi_struct {int dummy; } ;
struct iwl_rx_cmd_buffer {int /*<<< orphan*/  truesize; } ;
struct iwl_mvm {int /*<<< orphan*/  hw; } ;
struct ieee80211_sta {int dummy; } ;
struct ieee80211_hdr {int /*<<< orphan*/  frame_control; } ;

/* Variables and functions */
 unsigned int ieee80211_hdrlen (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ieee80211_rx_napi (int /*<<< orphan*/ ,struct ieee80211_sta*,struct sk_buff*,struct napi_struct*) ; 
 void* rxb_addr (struct iwl_rx_cmd_buffer*) ; 
 int rxb_offset (struct iwl_rx_cmd_buffer*) ; 
 int /*<<< orphan*/  rxb_steal_page (struct iwl_rx_cmd_buffer*) ; 
 int /*<<< orphan*/  skb_add_rx_frag (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skb_put_data (struct sk_buff*,struct ieee80211_hdr*,unsigned int) ; 
 int /*<<< orphan*/  skb_reserve (struct sk_buff*,unsigned int) ; 
 unsigned int skb_tailroom (struct sk_buff*) ; 

__attribute__((used)) static void iwl_mvm_pass_packet_to_mac80211(struct iwl_mvm *mvm,
					    struct ieee80211_sta *sta,
					    struct napi_struct *napi,
					    struct sk_buff *skb,
					    struct ieee80211_hdr *hdr, u16 len,
					    u8 crypt_len,
					    struct iwl_rx_cmd_buffer *rxb)
{
	unsigned int hdrlen = ieee80211_hdrlen(hdr->frame_control);
	unsigned int fraglen;

	/*
	 * The 'hdrlen' (plus the 8 bytes for the SNAP and the crypt_len,
	 * but those are all multiples of 4 long) all goes away, but we
	 * want the *end* of it, which is going to be the start of the IP
	 * header, to be aligned when it gets pulled in.
	 * The beginning of the skb->data is aligned on at least a 4-byte
	 * boundary after allocation. Everything here is aligned at least
	 * on a 2-byte boundary so we can just take hdrlen & 3 and pad by
	 * the result.
	 */
	skb_reserve(skb, hdrlen & 3);

	/* If frame is small enough to fit in skb->head, pull it completely.
	 * If not, only pull ieee80211_hdr (including crypto if present, and
	 * an additional 8 bytes for SNAP/ethertype, see below) so that
	 * splice() or TCP coalesce are more efficient.
	 *
	 * Since, in addition, ieee80211_data_to_8023() always pull in at
	 * least 8 bytes (possibly more for mesh) we can do the same here
	 * to save the cost of doing it later. That still doesn't pull in
	 * the actual IP header since the typical case has a SNAP header.
	 * If the latter changes (there are efforts in the standards group
	 * to do so) we should revisit this and ieee80211_data_to_8023().
	 */
	hdrlen = (len <= skb_tailroom(skb)) ? len : hdrlen + crypt_len + 8;

	skb_put_data(skb, hdr, hdrlen);
	fraglen = len - hdrlen;

	if (fraglen) {
		int offset = (void *)hdr + hdrlen -
			     rxb_addr(rxb) + rxb_offset(rxb);

		skb_add_rx_frag(skb, 0, rxb_steal_page(rxb), offset,
				fraglen, rxb->truesize);
	}

	ieee80211_rx_napi(mvm->hw, sta, skb, napi);
}