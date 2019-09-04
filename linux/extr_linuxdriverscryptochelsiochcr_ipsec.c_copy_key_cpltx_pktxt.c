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
struct sk_buff {unsigned int queue_mapping; } ;
struct TYPE_4__ {void* desc; int size; scalar_t__ stat; } ;
struct sge_eth_txq {TYPE_2__ q; } ;
struct port_info {unsigned int first_qset; struct adapter* adapter; } ;
struct net_device {int dummy; } ;
struct ipsec_sa_entry {int kctx_len; scalar_t__ key; scalar_t__ salt; int /*<<< orphan*/  key_ctx_hdr; } ;
struct TYPE_3__ {struct sge_eth_txq* ethtxq; } ;
struct adapter {TYPE_1__ sge; } ;
struct _key_ctx {void* salt; void* key; int /*<<< orphan*/  ctx_hdr; } ;

/* Variables and functions */
 int MAX_SALT ; 
 void* copy_cpltx_pktxt (struct sk_buff*,struct net_device*,void*) ; 
 scalar_t__ likely (int) ; 
 int /*<<< orphan*/  memcpy (void*,scalar_t__,int) ; 
 struct port_info* netdev_priv (struct net_device*) ; 

inline void *copy_key_cpltx_pktxt(struct sk_buff *skb,
				struct net_device *dev,
				void *pos,
				struct ipsec_sa_entry *sa_entry)
{
	struct _key_ctx *key_ctx;
	int left, eoq, key_len;
	struct sge_eth_txq *q;
	struct adapter *adap;
	struct port_info *pi;
	unsigned int qidx;

	pi = netdev_priv(dev);
	adap = pi->adapter;
	qidx = skb->queue_mapping;
	q = &adap->sge.ethtxq[qidx + pi->first_qset];
	key_len = sa_entry->kctx_len;

	/* end of queue, reset pos to start of queue */
	eoq = (void *)q->q.stat - pos;
	left = eoq;
	if (!eoq) {
		pos = q->q.desc;
		left = 64 * q->q.size;
	}

	/* Copy the Key context header */
	key_ctx = (struct _key_ctx *)pos;
	key_ctx->ctx_hdr = sa_entry->key_ctx_hdr;
	memcpy(key_ctx->salt, sa_entry->salt, MAX_SALT);
	pos += sizeof(struct _key_ctx);
	left -= sizeof(struct _key_ctx);

	if (likely(key_len <= left)) {
		memcpy(key_ctx->key, sa_entry->key, key_len);
		pos += key_len;
	} else {
		memcpy(pos, sa_entry->key, left);
		memcpy(q->q.desc, sa_entry->key + left,
		       key_len - left);
		pos = (u8 *)q->q.desc + (key_len - left);
	}
	/* Copy CPL TX PKT XT */
	pos = copy_cpltx_pktxt(skb, dev, pos);

	return pos;
}