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
struct net_device {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* copy_to_card ) (struct net_device*,int,int,struct arc_rfc1201*,int) ;} ;
struct arcnet_local {int /*<<< orphan*/  lastload_dest; TYPE_1__ hw; } ;
struct arc_rfc1201 {int* offset; int split_flag; int /*<<< orphan*/  dest; int /*<<< orphan*/  sequence; int /*<<< orphan*/  proto; } ;
struct arc_hardware {int* offset; int split_flag; int /*<<< orphan*/  dest; int /*<<< orphan*/  sequence; int /*<<< orphan*/  proto; } ;

/* Variables and functions */
 int ARC_HDR_SIZE ; 
 int MTU ; 
 int MinTU ; 
 int RFC1201_HDR_SIZE ; 
 int /*<<< orphan*/  htons (int) ; 
 struct arcnet_local* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  stub1 (struct net_device*,int,int,struct arc_rfc1201*,int) ; 
 int /*<<< orphan*/  stub2 (struct net_device*,int,int,struct arc_rfc1201*,int) ; 
 int /*<<< orphan*/  stub3 (struct net_device*,int,int,struct arc_rfc1201*,int) ; 

__attribute__((used)) static void load_pkt(struct net_device *dev, struct arc_hardware *hard,
		     struct arc_rfc1201 *soft, int softlen, int bufnum)
{
	struct arcnet_local *lp = netdev_priv(dev);
	int ofs;

	/* assume length <= XMTU: someone should have handled that by now. */

	if (softlen > MinTU) {
		hard->offset[0] = 0;
		hard->offset[1] = ofs = 512 - softlen;
	} else if (softlen > MTU) {	/* exception packet - add an extra header */
		struct arc_rfc1201 excsoft;

		excsoft.proto = soft->proto;
		excsoft.split_flag = 0xff;
		excsoft.sequence = htons(0xffff);

		hard->offset[0] = 0;
		ofs = 512 - softlen;
		hard->offset[1] = ofs - RFC1201_HDR_SIZE;
		lp->hw.copy_to_card(dev, bufnum, ofs - RFC1201_HDR_SIZE,
				    &excsoft, RFC1201_HDR_SIZE);
	} else {
		hard->offset[0] = ofs = 256 - softlen;
	}

	lp->hw.copy_to_card(dev, bufnum, 0, hard, ARC_HDR_SIZE);
	lp->hw.copy_to_card(dev, bufnum, ofs, soft, softlen);

	lp->lastload_dest = hard->dest;
}