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
struct sk_buff {unsigned int len; scalar_t__ data; } ;
struct nfp_app_bpf {TYPE_1__* app; } ;
struct cmsg_hdr {int type; int /*<<< orphan*/  tag; int /*<<< orphan*/  ver; } ;
typedef  enum nfp_bpf_cmsg_type { ____Placeholder_nfp_bpf_cmsg_type } nfp_bpf_cmsg_type ;
struct TYPE_2__ {int /*<<< orphan*/  ctrl; } ;

/* Variables and functions */
 int /*<<< orphan*/  CMSG_MAP_ABI_VERSION ; 
 int EIO ; 
 struct sk_buff* ERR_PTR (int) ; 
 scalar_t__ IS_ERR (struct sk_buff*) ; 
 scalar_t__ __CMSG_REPLY (int) ; 
 int /*<<< orphan*/  __nfp_app_ctrl_tx (TYPE_1__*,struct sk_buff*) ; 
 int /*<<< orphan*/  cmsg_warn (struct nfp_app_bpf*,char*,int,unsigned int,...) ; 
 int /*<<< orphan*/  cpu_to_be16 (int) ; 
 int /*<<< orphan*/  dev_kfree_skb_any (struct sk_buff*) ; 
 int nfp_bpf_alloc_tag (struct nfp_app_bpf*) ; 
 struct sk_buff* nfp_bpf_cmsg_wait_reply (struct nfp_app_bpf*,int,int) ; 
 int /*<<< orphan*/  nfp_ctrl_lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nfp_ctrl_unlock (int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct sk_buff *
nfp_bpf_cmsg_communicate(struct nfp_app_bpf *bpf, struct sk_buff *skb,
			 enum nfp_bpf_cmsg_type type, unsigned int reply_size)
{
	struct cmsg_hdr *hdr;
	int tag;

	nfp_ctrl_lock(bpf->app->ctrl);
	tag = nfp_bpf_alloc_tag(bpf);
	if (tag < 0) {
		nfp_ctrl_unlock(bpf->app->ctrl);
		dev_kfree_skb_any(skb);
		return ERR_PTR(tag);
	}

	hdr = (void *)skb->data;
	hdr->ver = CMSG_MAP_ABI_VERSION;
	hdr->type = type;
	hdr->tag = cpu_to_be16(tag);

	__nfp_app_ctrl_tx(bpf->app, skb);

	nfp_ctrl_unlock(bpf->app->ctrl);

	skb = nfp_bpf_cmsg_wait_reply(bpf, type, tag);
	if (IS_ERR(skb))
		return skb;

	hdr = (struct cmsg_hdr *)skb->data;
	if (hdr->type != __CMSG_REPLY(type)) {
		cmsg_warn(bpf, "cmsg drop - wrong type 0x%02x != 0x%02lx!\n",
			  hdr->type, __CMSG_REPLY(type));
		goto err_free;
	}
	/* 0 reply_size means caller will do the validation */
	if (reply_size && skb->len != reply_size) {
		cmsg_warn(bpf, "cmsg drop - type 0x%02x wrong size %d != %d!\n",
			  type, skb->len, reply_size);
		goto err_free;
	}

	return skb;
err_free:
	dev_kfree_skb_any(skb);
	return ERR_PTR(-EIO);
}