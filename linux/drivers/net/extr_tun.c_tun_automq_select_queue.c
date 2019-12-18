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
typedef  int u64 ;
typedef  int u32 ;
typedef  int u16 ;
struct tun_struct {int /*<<< orphan*/ * flows; int /*<<< orphan*/  numqueues; } ;
struct tun_flow_entry {int queue_index; } ;
struct sk_buff {int dummy; } ;

/* Variables and functions */
 int READ_ONCE (int /*<<< orphan*/ ) ; 
 int __skb_get_hash_symmetric (struct sk_buff*) ; 
 struct tun_flow_entry* tun_flow_find (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  tun_flow_save_rps_rxhash (struct tun_flow_entry*,int) ; 
 size_t tun_hashfn (int) ; 

__attribute__((used)) static u16 tun_automq_select_queue(struct tun_struct *tun, struct sk_buff *skb)
{
	struct tun_flow_entry *e;
	u32 txq = 0;
	u32 numqueues = 0;

	numqueues = READ_ONCE(tun->numqueues);

	txq = __skb_get_hash_symmetric(skb);
	e = tun_flow_find(&tun->flows[tun_hashfn(txq)], txq);
	if (e) {
		tun_flow_save_rps_rxhash(e, txq);
		txq = e->queue_index;
	} else {
		/* use multiply and shift instead of expensive divide */
		txq = ((u64)txq * numqueues) >> 32;
	}

	return txq;
}