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
struct sk_buff {scalar_t__ data; } ;
struct nfp_net {int /*<<< orphan*/  dp; } ;
struct nfp_crypto_reply_simple {int /*<<< orphan*/  error; } ;
typedef  enum nfp_ccm_type { ____Placeholder_nfp_ccm_type } nfp_ccm_type ;

/* Variables and functions */
 int NFP_CCM_TYPE_CRYPTO_DEL ; 
 int __nfp_ccm_mbox_communicate (struct nfp_net*,struct sk_buff*,int,int,int,int) ; 
 int be32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_consume_skb_any (struct sk_buff*) ; 
 int /*<<< orphan*/  nn_dp_warn (int /*<<< orphan*/ *,char*,char const*,int) ; 

__attribute__((used)) static int
nfp_net_tls_communicate_simple(struct nfp_net *nn, struct sk_buff *skb,
			       const char *name, enum nfp_ccm_type type)
{
	struct nfp_crypto_reply_simple *reply;
	int err;

	err = __nfp_ccm_mbox_communicate(nn, skb, type,
					 sizeof(*reply), sizeof(*reply),
					 type == NFP_CCM_TYPE_CRYPTO_DEL);
	if (err) {
		nn_dp_warn(&nn->dp, "failed to %s TLS: %d\n", name, err);
		return err;
	}

	reply = (void *)skb->data;
	err = -be32_to_cpu(reply->error);
	if (err)
		nn_dp_warn(&nn->dp, "failed to %s TLS, fw replied: %d\n",
			   name, err);
	dev_consume_skb_any(skb);

	return err;
}