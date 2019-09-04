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
struct net_device {int dummy; } ;
struct Outgoing {int segnum; int numsegs; int dataleft; scalar_t__ length; TYPE_2__* pkt; } ;
struct arcnet_local {struct Outgoing outgoing; } ;
struct arc_rfc1201 {int split_flag; int /*<<< orphan*/  sequence; int /*<<< orphan*/  proto; } ;
struct arc_hardware {int dummy; } ;
struct TYPE_3__ {scalar_t__ raw; struct arc_rfc1201 rfc1201; } ;
struct TYPE_4__ {TYPE_1__ soft; struct arc_hardware hard; } ;

/* Variables and functions */
 int /*<<< orphan*/  D_DURING ; 
 int RFC1201_HDR_SIZE ; 
 int XMTU ; 
 int /*<<< orphan*/  arc_printk (int /*<<< orphan*/ ,struct net_device*,char*,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  load_pkt (struct net_device*,struct arc_hardware*,struct arc_rfc1201*,int,int) ; 
 struct arcnet_local* netdev_priv (struct net_device*) ; 

__attribute__((used)) static int continue_tx(struct net_device *dev, int bufnum)
{
	struct arcnet_local *lp = netdev_priv(dev);
	struct Outgoing *out = &lp->outgoing;
	struct arc_hardware *hard = &out->pkt->hard;
	struct arc_rfc1201 *soft = &out->pkt->soft.rfc1201, *newsoft;
	int maxsegsize = XMTU - RFC1201_HDR_SIZE;
	int seglen;

	arc_printk(D_DURING, dev,
		   "rfc1201 continue_tx: loading segment %d(+1) of %d (seq=%d)\n",
		   out->segnum, out->numsegs, soft->sequence);

	/* the "new" soft header comes right before the data chunk */
	newsoft = (struct arc_rfc1201 *)
	    (out->pkt->soft.raw + out->length - out->dataleft);

	if (!out->segnum)	/* first packet; newsoft == soft */
		newsoft->split_flag = ((out->numsegs - 2) << 1) | 1;
	else {
		newsoft->split_flag = out->segnum << 1;
		newsoft->proto = soft->proto;
		newsoft->sequence = soft->sequence;
	}

	seglen = maxsegsize;
	if (seglen > out->dataleft)
		seglen = out->dataleft;
	out->dataleft -= seglen;

	load_pkt(dev, hard, newsoft, seglen + RFC1201_HDR_SIZE, bufnum);

	out->segnum++;
	if (out->segnum >= out->numsegs)
		return 1;
	else
		return 0;
}