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
struct sk_buff {int dummy; } ;
struct nfp_net {int dummy; } ;
struct nfp_crypto_reply_simple {int dummy; } ;
typedef  int /*<<< orphan*/  gfp_t ;

/* Variables and functions */
 struct sk_buff* nfp_ccm_mbox_msg_alloc (struct nfp_net*,size_t,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct sk_buff *
nfp_net_tls_alloc_simple(struct nfp_net *nn, size_t req_sz, gfp_t flags)
{
	return nfp_ccm_mbox_msg_alloc(nn, req_sz,
				      sizeof(struct nfp_crypto_reply_simple),
				      flags);
}