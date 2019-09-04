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
typedef  int /*<<< orphan*/  u32 ;
struct sk_buff_head {int dummy; } ;
struct sk_buff {TYPE_1__* dev; } ;
struct frame {int flags; int /*<<< orphan*/  sent; int /*<<< orphan*/  tag; struct sk_buff* skb; struct aoetgt* t; } ;
struct aoetgt {TYPE_2__* ifp; int /*<<< orphan*/  addr; int /*<<< orphan*/  nout; } ;
struct aoedev {int /*<<< orphan*/  aoeminor; int /*<<< orphan*/  aoemajor; } ;
struct aoe_hdr {int /*<<< orphan*/  src; int /*<<< orphan*/  dst; int /*<<< orphan*/  tag; } ;
typedef  int /*<<< orphan*/  buf ;
struct TYPE_4__ {TYPE_1__* nd; } ;
struct TYPE_3__ {int /*<<< orphan*/  dev_addr; } ;

/* Variables and functions */
 int FFL_PROBE ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  __skb_queue_head_init (struct sk_buff_head*) ; 
 int /*<<< orphan*/  __skb_queue_tail (struct sk_buff_head*,struct sk_buff*) ; 
 int /*<<< orphan*/  aoechr_error (char*) ; 
 int /*<<< orphan*/  aoenet_xmit (struct sk_buff_head*) ; 
 int /*<<< orphan*/  cpu_to_be32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fhash (struct frame*) ; 
 int /*<<< orphan*/ * ifrotate (struct aoetgt*) ; 
 int /*<<< orphan*/  jiffies ; 
 int /*<<< orphan*/  ktcomplete (struct frame*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ktime_get () ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  newtag (struct aoedev*) ; 
 int /*<<< orphan*/  pr_info (char*) ; 
 struct sk_buff* skb_clone (struct sk_buff*,int /*<<< orphan*/ ) ; 
 scalar_t__ skb_mac_header (struct sk_buff*) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
resend(struct aoedev *d, struct frame *f)
{
	struct sk_buff *skb;
	struct sk_buff_head queue;
	struct aoe_hdr *h;
	struct aoetgt *t;
	char buf[128];
	u32 n;

	t = f->t;
	n = newtag(d);
	skb = f->skb;
	if (ifrotate(t) == NULL) {
		/* probably can't happen, but set it up to fail anyway */
		pr_info("aoe: resend: no interfaces to rotate to.\n");
		ktcomplete(f, NULL);
		return;
	}
	h = (struct aoe_hdr *) skb_mac_header(skb);

	if (!(f->flags & FFL_PROBE)) {
		snprintf(buf, sizeof(buf),
			"%15s e%ld.%d oldtag=%08x@%08lx newtag=%08x s=%pm d=%pm nout=%d\n",
			"retransmit", d->aoemajor, d->aoeminor,
			f->tag, jiffies, n,
			h->src, h->dst, t->nout);
		aoechr_error(buf);
	}

	f->tag = n;
	fhash(f);
	h->tag = cpu_to_be32(n);
	memcpy(h->dst, t->addr, sizeof h->dst);
	memcpy(h->src, t->ifp->nd->dev_addr, sizeof h->src);

	skb->dev = t->ifp->nd;
	skb = skb_clone(skb, GFP_ATOMIC);
	if (skb == NULL)
		return;
	f->sent = ktime_get();
	__skb_queue_head_init(&queue);
	__skb_queue_tail(&queue, skb);
	aoenet_xmit(&queue);
}