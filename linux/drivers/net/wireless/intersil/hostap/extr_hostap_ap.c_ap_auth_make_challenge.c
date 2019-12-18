#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct sk_buff {int dummy; } ;
struct ap_data {TYPE_1__* crypt; int /*<<< orphan*/  crypt_priv; } ;
struct TYPE_2__ {scalar_t__ extra_mpdu_prefix_len; scalar_t__ (* encrypt_mpdu ) (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;scalar_t__ extra_mpdu_postfix_len; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUG_AP ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  PDEBUG (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ WLAN_AUTH_CHALLENGE_LEN ; 
 int /*<<< orphan*/  ap_crypt_init (struct ap_data*) ; 
 struct sk_buff* dev_alloc_skb (scalar_t__) ; 
 int /*<<< orphan*/  dev_kfree_skb (struct sk_buff*) ; 
 int /*<<< orphan*/  kfree (char*) ; 
 char* kmalloc (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skb_copy_from_linear_data_offset (struct sk_buff*,scalar_t__,char*,scalar_t__) ; 
 int /*<<< orphan*/  skb_put_zero (struct sk_buff*,scalar_t__) ; 
 int /*<<< orphan*/  skb_reserve (struct sk_buff*,scalar_t__) ; 
 scalar_t__ stub1 (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static char * ap_auth_make_challenge(struct ap_data *ap)
{
	char *tmpbuf;
	struct sk_buff *skb;

	if (ap->crypt == NULL) {
		ap_crypt_init(ap);
		if (ap->crypt == NULL)
			return NULL;
	}

	tmpbuf = kmalloc(WLAN_AUTH_CHALLENGE_LEN, GFP_ATOMIC);
	if (tmpbuf == NULL) {
		PDEBUG(DEBUG_AP, "AP: kmalloc failed for challenge\n");
		return NULL;
	}

	skb = dev_alloc_skb(WLAN_AUTH_CHALLENGE_LEN +
			    ap->crypt->extra_mpdu_prefix_len +
			    ap->crypt->extra_mpdu_postfix_len);
	if (skb == NULL) {
		kfree(tmpbuf);
		return NULL;
	}

	skb_reserve(skb, ap->crypt->extra_mpdu_prefix_len);
	skb_put_zero(skb, WLAN_AUTH_CHALLENGE_LEN);
	if (ap->crypt->encrypt_mpdu(skb, 0, ap->crypt_priv)) {
		dev_kfree_skb(skb);
		kfree(tmpbuf);
		return NULL;
	}

	skb_copy_from_linear_data_offset(skb, ap->crypt->extra_mpdu_prefix_len,
					 tmpbuf, WLAN_AUTH_CHALLENGE_LEN);
	dev_kfree_skb(skb);

	return tmpbuf;
}