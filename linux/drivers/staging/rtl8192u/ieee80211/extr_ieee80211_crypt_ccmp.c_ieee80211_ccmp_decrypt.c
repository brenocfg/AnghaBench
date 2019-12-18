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
typedef  int u8 ;
struct sk_buff {int len; int* data; int /*<<< orphan*/  dev; scalar_t__ cb; } ;
struct scatterlist {int dummy; } ;
struct rtl_80211_hdr_4addr {int /*<<< orphan*/  addr2; } ;
struct ieee80211_ccmp_data {int key_idx; int* rx_aad; int /*<<< orphan*/  rx_pn; int /*<<< orphan*/  dot11RSNAStatsCCMPDecryptErrors; int /*<<< orphan*/  tfm; int /*<<< orphan*/  dot11RSNAStatsCCMPReplays; int /*<<< orphan*/  key_set; int /*<<< orphan*/  dot11RSNAStatsCCMPFormatErrors; } ;
struct cb_desc {int /*<<< orphan*/  bHwSec; } ;
struct aead_request {int dummy; } ;

/* Variables and functions */
 int AES_BLOCK_LEN ; 
 int BIT (int) ; 
 int CCMP_HDR_LEN ; 
 int CCMP_MIC_LEN ; 
 int /*<<< orphan*/  CCMP_PN_LEN ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 scalar_t__ MAX_DEV_ADDR_SIZE ; 
 struct aead_request* aead_request_alloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  aead_request_free (struct aead_request*) ; 
 int /*<<< orphan*/  aead_request_set_ad (struct aead_request*,int) ; 
 int /*<<< orphan*/  aead_request_set_callback (struct aead_request*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  aead_request_set_crypt (struct aead_request*,struct scatterlist*,struct scatterlist*,size_t,int*) ; 
 int ccmp_init_iv_and_aad (struct rtl_80211_hdr_4addr*,int*,int*,int*) ; 
 int crypto_aead_decrypt (struct aead_request*) ; 
 scalar_t__ memcmp (int*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memmove (int*,int*,int) ; 
 scalar_t__ net_ratelimit () ; 
 int /*<<< orphan*/  netdev_dbg (int /*<<< orphan*/ ,char*,int,...) ; 
 int /*<<< orphan*/  sg_init_table (struct scatterlist*,int) ; 
 int /*<<< orphan*/  sg_set_buf (struct scatterlist*,int*,size_t) ; 
 int /*<<< orphan*/  skb_pull (struct sk_buff*,int) ; 
 int /*<<< orphan*/  skb_trim (struct sk_buff*,int) ; 

__attribute__((used)) static int ieee80211_ccmp_decrypt(struct sk_buff *skb, int hdr_len, void *priv)
{
	struct ieee80211_ccmp_data *key = priv;
	u8 keyidx, *pos;
	struct rtl_80211_hdr_4addr *hdr;
	struct cb_desc *tcb_desc = (struct cb_desc *)(skb->cb + MAX_DEV_ADDR_SIZE);
	u8 pn[6];

	if (skb->len < hdr_len + CCMP_HDR_LEN + CCMP_MIC_LEN) {
		key->dot11RSNAStatsCCMPFormatErrors++;
		return -1;
	}

	hdr = (struct rtl_80211_hdr_4addr *)skb->data;
	pos = skb->data + hdr_len;
	keyidx = pos[3];
	if (!(keyidx & BIT(5))) {
		if (net_ratelimit()) {
			netdev_dbg(skb->dev, "CCMP: received packet without ExtIV flag from %pM\n",
				   hdr->addr2);
		}
		key->dot11RSNAStatsCCMPFormatErrors++;
		return -2;
	}
	keyidx >>= 6;
	if (key->key_idx != keyidx) {
		netdev_dbg(skb->dev, "CCMP: RX tkey->key_idx=%d frame keyidx=%d priv=%p\n",
			   key->key_idx, keyidx, priv);
		return -6;
	}
	if (!key->key_set) {
		if (net_ratelimit()) {
			netdev_dbg(skb->dev, "CCMP: received packet from %pM with keyid=%d that does not have a configured key\n",
				   hdr->addr2, keyidx);
		}
		return -3;
	}

	pn[0] = pos[7];
	pn[1] = pos[6];
	pn[2] = pos[5];
	pn[3] = pos[4];
	pn[4] = pos[1];
	pn[5] = pos[0];
	pos += 8;

	if (memcmp(pn, key->rx_pn, CCMP_PN_LEN) <= 0) {
		if (net_ratelimit()) {
			netdev_dbg(skb->dev, "CCMP: replay detected: STA=%pM previous PN %pm received PN %pm\n",
				   hdr->addr2, key->rx_pn, pn);
		}
		key->dot11RSNAStatsCCMPReplays++;
		return -4;
	}
	if (!tcb_desc->bHwSec) {
		struct aead_request *req;
		struct scatterlist sg[2];
		u8 *aad = key->rx_aad;
		u8 iv[AES_BLOCK_LEN];
		int aad_len, ret;
		size_t data_len = skb->len - hdr_len - CCMP_HDR_LEN;

		req = aead_request_alloc(key->tfm, GFP_ATOMIC);
		if (!req)
			return -ENOMEM;

		aad_len = ccmp_init_iv_and_aad(hdr, pn, iv, aad);

		sg_init_table(sg, 2);
		sg_set_buf(&sg[0], aad, aad_len);
		sg_set_buf(&sg[1], pos, data_len);

		aead_request_set_callback(req, 0, NULL, NULL);
		aead_request_set_ad(req, aad_len);
		aead_request_set_crypt(req, sg, sg, data_len, iv);

		ret = crypto_aead_decrypt(req);
		aead_request_free(req);

		if (ret) {
			if (net_ratelimit()) {
				netdev_dbg(skb->dev, "CCMP: decrypt failed: STA=%pM\n",
					   hdr->addr2);
			}
			key->dot11RSNAStatsCCMPDecryptErrors++;
			return -5;
		}

		memcpy(key->rx_pn, pn, CCMP_PN_LEN);
	}
	/* Remove hdr and MIC */
	memmove(skb->data + CCMP_HDR_LEN, skb->data, hdr_len);
	skb_pull(skb, CCMP_HDR_LEN);
	skb_trim(skb, skb->len - CCMP_MIC_LEN);

	return keyidx;
}