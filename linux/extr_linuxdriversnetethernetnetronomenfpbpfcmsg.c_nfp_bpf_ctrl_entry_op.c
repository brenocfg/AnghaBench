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
typedef  int /*<<< orphan*/  u8 ;
typedef  int u64 ;
struct sk_buff {scalar_t__ data; } ;
struct nfp_bpf_map {int tid; struct nfp_app_bpf* bpf; } ;
struct nfp_app_bpf {int dummy; } ;
struct cmsg_req_map_op {TYPE_1__* elem; void* flags; void* count; void* tid; } ;
struct cmsg_reply_map_op {TYPE_2__* elem; int /*<<< orphan*/  reply_hdr; } ;
struct bpf_map {int /*<<< orphan*/  value_size; int /*<<< orphan*/  key_size; } ;
struct bpf_offloaded_map {struct bpf_map map; struct nfp_bpf_map* dev_priv; } ;
typedef  enum nfp_bpf_cmsg_type { ____Placeholder_nfp_bpf_cmsg_type } nfp_bpf_cmsg_type ;
struct TYPE_4__ {int /*<<< orphan*/  value; int /*<<< orphan*/  key; } ;
struct TYPE_3__ {int /*<<< orphan*/  value; int /*<<< orphan*/  key; } ;

/* Variables and functions */
 int ENOMEM ; 
 int EOPNOTSUPP ; 
 scalar_t__ IS_ERR (struct sk_buff*) ; 
 int PTR_ERR (struct sk_buff*) ; 
 void* cpu_to_be32 (int) ; 
 int /*<<< orphan*/  dev_consume_skb_any (struct sk_buff*) ; 
 int /*<<< orphan*/  dev_kfree_skb_any (struct sk_buff*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct sk_buff* nfp_bpf_cmsg_communicate (struct nfp_app_bpf*,struct sk_buff*,int,int) ; 
 struct sk_buff* nfp_bpf_cmsg_map_req_alloc (struct nfp_app_bpf*,int) ; 
 int nfp_bpf_ctrl_rc_to_errno (struct nfp_app_bpf*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
nfp_bpf_ctrl_entry_op(struct bpf_offloaded_map *offmap,
		      enum nfp_bpf_cmsg_type op,
		      u8 *key, u8 *value, u64 flags, u8 *out_key, u8 *out_value)
{
	struct nfp_bpf_map *nfp_map = offmap->dev_priv;
	struct nfp_app_bpf *bpf = nfp_map->bpf;
	struct bpf_map *map = &offmap->map;
	struct cmsg_reply_map_op *reply;
	struct cmsg_req_map_op *req;
	struct sk_buff *skb;
	int err;

	/* FW messages have no space for more than 32 bits of flags */
	if (flags >> 32)
		return -EOPNOTSUPP;

	skb = nfp_bpf_cmsg_map_req_alloc(bpf, 1);
	if (!skb)
		return -ENOMEM;

	req = (void *)skb->data;
	req->tid = cpu_to_be32(nfp_map->tid);
	req->count = cpu_to_be32(1);
	req->flags = cpu_to_be32(flags);

	/* Copy inputs */
	if (key)
		memcpy(&req->elem[0].key, key, map->key_size);
	if (value)
		memcpy(&req->elem[0].value, value, map->value_size);

	skb = nfp_bpf_cmsg_communicate(bpf, skb, op,
				       sizeof(*reply) + sizeof(*reply->elem));
	if (IS_ERR(skb))
		return PTR_ERR(skb);

	reply = (void *)skb->data;
	err = nfp_bpf_ctrl_rc_to_errno(bpf, &reply->reply_hdr);
	if (err)
		goto err_free;

	/* Copy outputs */
	if (out_key)
		memcpy(out_key, &reply->elem[0].key, map->key_size);
	if (out_value)
		memcpy(out_value, &reply->elem[0].value, map->value_size);

	dev_consume_skb_any(skb);

	return 0;
err_free:
	dev_kfree_skb_any(skb);
	return err;
}