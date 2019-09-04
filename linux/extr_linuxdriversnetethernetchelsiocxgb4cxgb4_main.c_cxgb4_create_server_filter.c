#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
struct net_device {int dummy; } ;
struct TYPE_10__ {unsigned char iport; int /*<<< orphan*/  proto; int /*<<< orphan*/ * lip; int /*<<< orphan*/  lport; } ;
struct TYPE_9__ {int* lip; unsigned char iport; int /*<<< orphan*/  proto; int /*<<< orphan*/  lport; } ;
struct TYPE_12__ {int dirsteer; unsigned int iq; int rpttid; TYPE_4__ mask; TYPE_3__ val; } ;
struct filter_entry {int locked; scalar_t__ tid; TYPE_6__ fs; scalar_t__ valid; } ;
struct ch_filter_specification {int dummy; } ;
struct TYPE_11__ {scalar_t__ ftid_base; struct filter_entry* ftid_tab; scalar_t__ nftids; scalar_t__ sftid_base; } ;
struct TYPE_7__ {int vlan_pri_map; } ;
struct TYPE_8__ {TYPE_1__ tp; } ;
struct adapter {TYPE_5__ tids; TYPE_2__ params; } ;
typedef  int /*<<< orphan*/  __be32 ;
typedef  int /*<<< orphan*/  __be16 ;

/* Variables and functions */
 int /*<<< orphan*/  IPPROTO_TCP ; 
 int PORT_F ; 
 int PROTOCOL_F ; 
 int /*<<< orphan*/  clear_filter (struct adapter*,struct filter_entry*) ; 
 int /*<<< orphan*/  cpu_to_be16 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (TYPE_6__*,int /*<<< orphan*/ ,int) ; 
 struct adapter* netdev2adap (struct net_device const*) ; 
 int set_filter_wr (struct adapter*,unsigned int) ; 
 int writable_filter (struct filter_entry*) ; 

int cxgb4_create_server_filter(const struct net_device *dev, unsigned int stid,
		__be32 sip, __be16 sport, __be16 vlan,
		unsigned int queue, unsigned char port, unsigned char mask)
{
	int ret;
	struct filter_entry *f;
	struct adapter *adap;
	int i;
	u8 *val;

	adap = netdev2adap(dev);

	/* Adjust stid to correct filter index */
	stid -= adap->tids.sftid_base;
	stid += adap->tids.nftids;

	/* Check to make sure the filter requested is writable ...
	 */
	f = &adap->tids.ftid_tab[stid];
	ret = writable_filter(f);
	if (ret)
		return ret;

	/* Clear out any old resources being used by the filter before
	 * we start constructing the new filter.
	 */
	if (f->valid)
		clear_filter(adap, f);

	/* Clear out filter specifications */
	memset(&f->fs, 0, sizeof(struct ch_filter_specification));
	f->fs.val.lport = cpu_to_be16(sport);
	f->fs.mask.lport  = ~0;
	val = (u8 *)&sip;
	if ((val[0] | val[1] | val[2] | val[3]) != 0) {
		for (i = 0; i < 4; i++) {
			f->fs.val.lip[i] = val[i];
			f->fs.mask.lip[i] = ~0;
		}
		if (adap->params.tp.vlan_pri_map & PORT_F) {
			f->fs.val.iport = port;
			f->fs.mask.iport = mask;
		}
	}

	if (adap->params.tp.vlan_pri_map & PROTOCOL_F) {
		f->fs.val.proto = IPPROTO_TCP;
		f->fs.mask.proto = ~0;
	}

	f->fs.dirsteer = 1;
	f->fs.iq = queue;
	/* Mark filter as locked */
	f->locked = 1;
	f->fs.rpttid = 1;

	/* Save the actual tid. We need this to get the corresponding
	 * filter entry structure in filter_rpl.
	 */
	f->tid = stid + adap->tids.ftid_base;
	ret = set_filter_wr(adap, stid);
	if (ret) {
		clear_filter(adap, f);
		return ret;
	}

	return 0;
}