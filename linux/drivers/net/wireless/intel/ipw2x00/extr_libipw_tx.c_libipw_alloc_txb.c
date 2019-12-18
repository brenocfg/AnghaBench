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
struct libipw_txb {int nr_frags; int frag_size; int /*<<< orphan*/ * fragments; } ;
typedef  int /*<<< orphan*/  gfp_t ;

/* Variables and functions */
 int /*<<< orphan*/  __dev_alloc_skb (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_kfree_skb_any (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct libipw_txb*) ; 
 struct libipw_txb* kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct libipw_txb*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  skb_reserve (int /*<<< orphan*/ ,int) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static struct libipw_txb *libipw_alloc_txb(int nr_frags, int txb_size,
						 int headroom, gfp_t gfp_mask)
{
	struct libipw_txb *txb;
	int i;
	txb = kmalloc(sizeof(struct libipw_txb) + (sizeof(u8 *) * nr_frags),
		      gfp_mask);
	if (!txb)
		return NULL;

	memset(txb, 0, sizeof(struct libipw_txb));
	txb->nr_frags = nr_frags;
	txb->frag_size = txb_size;

	for (i = 0; i < nr_frags; i++) {
		txb->fragments[i] = __dev_alloc_skb(txb_size + headroom,
						    gfp_mask);
		if (unlikely(!txb->fragments[i])) {
			i--;
			break;
		}
		skb_reserve(txb->fragments[i], headroom);
	}
	if (unlikely(i != nr_frags)) {
		while (i >= 0)
			dev_kfree_skb_any(txb->fragments[i--]);
		kfree(txb);
		return NULL;
	}
	return txb;
}