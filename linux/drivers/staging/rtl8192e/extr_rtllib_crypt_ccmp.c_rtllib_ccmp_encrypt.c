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
struct sk_buff {int len; scalar_t__ data; scalar_t__ cb; } ;
struct scatterlist {int dummy; } ;
struct rtllib_hdr_4addr {int dummy; } ;
struct rtllib_ccmp_data {int key_idx; int /*<<< orphan*/ * tx_pn; int /*<<< orphan*/  tfm; int /*<<< orphan*/ * tx_aad; } ;
struct cb_desc {int /*<<< orphan*/  bHwSec; } ;
struct aead_request {int dummy; } ;

/* Variables and functions */
 int AES_BLOCK_LEN ; 
 scalar_t__ CCMP_HDR_LEN ; 
 int CCMP_MIC_LEN ; 
 int CCMP_PN_LEN ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 scalar_t__ MAX_DEV_ADDR_SIZE ; 
 struct aead_request* aead_request_alloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  aead_request_free (struct aead_request*) ; 
 int /*<<< orphan*/  aead_request_set_ad (struct aead_request*,int) ; 
 int /*<<< orphan*/  aead_request_set_callback (struct aead_request*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  aead_request_set_crypt (struct aead_request*,struct scatterlist*,struct scatterlist*,int,int /*<<< orphan*/ *) ; 
 int ccmp_init_iv_and_aad (struct rtllib_hdr_4addr*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int crypto_aead_encrypt (struct aead_request*) ; 
 int /*<<< orphan*/  memmove (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  sg_init_table (struct scatterlist*,int) ; 
 int /*<<< orphan*/  sg_set_buf (struct scatterlist*,scalar_t__,int) ; 
 scalar_t__ skb_headroom (struct sk_buff*) ; 
 int /*<<< orphan*/ * skb_push (struct sk_buff*,scalar_t__) ; 
 int /*<<< orphan*/  skb_put (struct sk_buff*,int) ; 
 int skb_tailroom (struct sk_buff*) ; 

__attribute__((used)) static int rtllib_ccmp_encrypt(struct sk_buff *skb, int hdr_len, void *priv)
{
	struct rtllib_ccmp_data *key = priv;
	int i;
	u8 *pos;
	struct rtllib_hdr_4addr *hdr;
	struct cb_desc *tcb_desc = (struct cb_desc *)(skb->cb +
				    MAX_DEV_ADDR_SIZE);
	if (skb_headroom(skb) < CCMP_HDR_LEN ||
	    skb_tailroom(skb) < CCMP_MIC_LEN ||
	    skb->len < hdr_len)
		return -1;

	pos = skb_push(skb, CCMP_HDR_LEN);
	memmove(pos, pos + CCMP_HDR_LEN, hdr_len);
	pos += hdr_len;

	i = CCMP_PN_LEN - 1;
	while (i >= 0) {
		key->tx_pn[i]++;
		if (key->tx_pn[i] != 0)
			break;
		i--;
	}

	*pos++ = key->tx_pn[5];
	*pos++ = key->tx_pn[4];
	*pos++ = 0;
	*pos++ = (key->key_idx << 6) | (1 << 5) /* Ext IV included */;
	*pos++ = key->tx_pn[3];
	*pos++ = key->tx_pn[2];
	*pos++ = key->tx_pn[1];
	*pos++ = key->tx_pn[0];

	hdr = (struct rtllib_hdr_4addr *) skb->data;
	if (!tcb_desc->bHwSec) {
		struct aead_request *req;
		struct scatterlist sg[2];
		u8 *aad = key->tx_aad;
		u8 iv[AES_BLOCK_LEN];
		int aad_len, ret;
		int data_len = skb->len - hdr_len - CCMP_HDR_LEN;

		req = aead_request_alloc(key->tfm, GFP_ATOMIC);
		if (!req)
			return -ENOMEM;

		aad_len = ccmp_init_iv_and_aad(hdr, key->tx_pn, iv, aad);

		skb_put(skb, CCMP_MIC_LEN);
		sg_init_table(sg, 2);
		sg_set_buf(&sg[0], aad, aad_len);
		sg_set_buf(&sg[1], skb->data + hdr_len + CCMP_HDR_LEN,
			   data_len + CCMP_MIC_LEN);

		aead_request_set_callback(req, 0, NULL, NULL);
		aead_request_set_ad(req, aad_len);
		aead_request_set_crypt(req, sg, sg, data_len, iv);

		ret = crypto_aead_encrypt(req);
		aead_request_free(req);

		return ret;
	}

	return 0;
}