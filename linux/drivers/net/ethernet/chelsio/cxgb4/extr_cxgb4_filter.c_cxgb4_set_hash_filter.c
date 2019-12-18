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
typedef  int /*<<< orphan*/  u8 ;
typedef  int u32 ;
struct tid_info {int dummy; } ;
struct sk_buff {int dummy; } ;
struct port_info {int /*<<< orphan*/  viid; } ;
struct net_device {int dummy; } ;
struct TYPE_10__ {int ovlan; int pf; int vf; int ovlan_vld; int pfvf_vld; int iport; scalar_t__ encap_vld; int /*<<< orphan*/  lip; int /*<<< orphan*/  vni; } ;
struct TYPE_9__ {int ovlan; int pf; int vf; int ovlan_vld; int pfvf_vld; int /*<<< orphan*/  vni; } ;
struct ch_filter_specification {int iq; TYPE_4__ val; scalar_t__ type; TYPE_3__ mask; int /*<<< orphan*/  smac; scalar_t__ newsmac; int /*<<< orphan*/  dmac; int /*<<< orphan*/  eport; int /*<<< orphan*/  vlan; scalar_t__ newvlan; scalar_t__ newdmac; } ;
struct filter_entry {int pending; int /*<<< orphan*/ * l2t; int /*<<< orphan*/ * smt; struct ch_filter_specification fs; struct net_device* dev; struct filter_ctx* ctx; } ;
struct filter_ctx {int dummy; } ;
struct cpl_t6_act_open_req {int dummy; } ;
struct TYPE_11__ {int abs_id; } ;
struct TYPE_12__ {TYPE_5__ fw_evtq; } ;
struct TYPE_7__ {int ingress_config; } ;
struct TYPE_8__ {TYPE_1__ tp; } ;
struct adapter {TYPE_6__ sge; TYPE_2__ params; struct tid_info tids; } ;

/* Variables and functions */
 int /*<<< orphan*/  CPL_PRIORITY_SETUP ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int USE_ENC_IDX_F ; 
 int VNIC_F ; 
 struct sk_buff* alloc_skb (int,int /*<<< orphan*/ ) ; 
 int cxgb4_alloc_atid (struct tid_info*,struct filter_entry*) ; 
 int cxgb4_clip_get (struct net_device*,int const*,int) ; 
 int /*<<< orphan*/  cxgb4_clip_release (struct net_device*,int const*,int) ; 
 int /*<<< orphan*/  cxgb4_free_atid (struct tid_info*,int) ; 
 int /*<<< orphan*/  cxgb4_l2t_release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * cxgb4_smt_alloc_switching (struct net_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cxgb4_smt_release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fill_default_mask (struct ch_filter_specification*) ; 
 int get_filter_steerq (struct net_device*,struct ch_filter_specification*) ; 
 int /*<<< orphan*/  kfree (struct filter_entry*) ; 
 struct filter_entry* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mk_act_open_req (struct filter_entry*,struct sk_buff*,int,struct adapter*) ; 
 int /*<<< orphan*/  mk_act_open_req6 (struct filter_entry*,struct sk_buff*,int,struct adapter*) ; 
 struct adapter* netdev2adap (struct net_device*) ; 
 struct port_info* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  set_wr_txq (struct sk_buff*,int /*<<< orphan*/ ,int) ; 
 int t4_alloc_encap_mac_filt (struct adapter*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  t4_free_encap_mac_filt (struct adapter*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/ * t4_l2t_alloc_switching (struct adapter*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  t4_ofld_send (struct adapter*,struct sk_buff*) ; 
 int validate_filter (struct net_device*,struct ch_filter_specification*) ; 

__attribute__((used)) static int cxgb4_set_hash_filter(struct net_device *dev,
				 struct ch_filter_specification *fs,
				 struct filter_ctx *ctx)
{
	struct adapter *adapter = netdev2adap(dev);
	struct port_info *pi = netdev_priv(dev);
	struct tid_info *t = &adapter->tids;
	struct filter_entry *f;
	struct sk_buff *skb;
	int iq, atid, size;
	int ret = 0;
	u32 iconf;

	fill_default_mask(fs);
	ret = validate_filter(dev, fs);
	if (ret)
		return ret;

	iq = get_filter_steerq(dev, fs);
	if (iq < 0)
		return iq;

	f = kzalloc(sizeof(*f), GFP_KERNEL);
	if (!f)
		return -ENOMEM;

	f->fs = *fs;
	f->ctx = ctx;
	f->dev = dev;
	f->fs.iq = iq;

	/* If the new filter requires loopback Destination MAC and/or VLAN
	 * rewriting then we need to allocate a Layer 2 Table (L2T) entry for
	 * the filter.
	 */
	if (f->fs.newdmac || f->fs.newvlan) {
		/* allocate L2T entry for new filter */
		f->l2t = t4_l2t_alloc_switching(adapter, f->fs.vlan,
						f->fs.eport, f->fs.dmac);
		if (!f->l2t) {
			ret = -ENOMEM;
			goto out_err;
		}
	}

	/* If the new filter requires loopback Source MAC rewriting then
	 * we need to allocate a SMT entry for the filter.
	 */
	if (f->fs.newsmac) {
		f->smt = cxgb4_smt_alloc_switching(f->dev, f->fs.smac);
		if (!f->smt) {
			if (f->l2t) {
				cxgb4_l2t_release(f->l2t);
				f->l2t = NULL;
			}
			ret = -ENOMEM;
			goto free_l2t;
		}
	}

	atid = cxgb4_alloc_atid(t, f);
	if (atid < 0) {
		ret = atid;
		goto free_smt;
	}

	iconf = adapter->params.tp.ingress_config;
	if (iconf & VNIC_F) {
		f->fs.val.ovlan = (fs->val.pf << 13) | fs->val.vf;
		f->fs.mask.ovlan = (fs->mask.pf << 13) | fs->mask.vf;
		f->fs.val.ovlan_vld = fs->val.pfvf_vld;
		f->fs.mask.ovlan_vld = fs->mask.pfvf_vld;
	} else if (iconf & USE_ENC_IDX_F) {
		if (f->fs.val.encap_vld) {
			struct port_info *pi = netdev_priv(f->dev);
			u8 match_all_mac[] = { 0, 0, 0, 0, 0, 0 };

			/* allocate MPS TCAM entry */
			ret = t4_alloc_encap_mac_filt(adapter, pi->viid,
						      match_all_mac,
						      match_all_mac,
						      f->fs.val.vni,
						      f->fs.mask.vni,
						      0, 1, 1);
			if (ret < 0)
				goto free_atid;

			f->fs.val.ovlan = ret;
			f->fs.mask.ovlan = 0xffff;
			f->fs.val.ovlan_vld = 1;
			f->fs.mask.ovlan_vld = 1;
		}
	}

	size = sizeof(struct cpl_t6_act_open_req);
	if (f->fs.type) {
		ret = cxgb4_clip_get(f->dev, (const u32 *)&f->fs.val.lip, 1);
		if (ret)
			goto free_mps;

		skb = alloc_skb(size, GFP_KERNEL);
		if (!skb) {
			ret = -ENOMEM;
			goto free_clip;
		}

		mk_act_open_req6(f, skb,
				 ((adapter->sge.fw_evtq.abs_id << 14) | atid),
				 adapter);
	} else {
		skb = alloc_skb(size, GFP_KERNEL);
		if (!skb) {
			ret = -ENOMEM;
			goto free_mps;
		}

		mk_act_open_req(f, skb,
				((adapter->sge.fw_evtq.abs_id << 14) | atid),
				adapter);
	}

	f->pending = 1;
	set_wr_txq(skb, CPL_PRIORITY_SETUP, f->fs.val.iport & 0x3);
	t4_ofld_send(adapter, skb);
	return 0;

free_clip:
	cxgb4_clip_release(f->dev, (const u32 *)&f->fs.val.lip, 1);

free_mps:
	if (f->fs.val.encap_vld && f->fs.val.ovlan_vld)
		t4_free_encap_mac_filt(adapter, pi->viid, f->fs.val.ovlan, 1);

free_atid:
	cxgb4_free_atid(t, atid);

free_smt:
	if (f->smt) {
		cxgb4_smt_release(f->smt);
		f->smt = NULL;
	}

free_l2t:
	if (f->l2t) {
		cxgb4_l2t_release(f->l2t);
		f->l2t = NULL;
	}

out_err:
	kfree(f);
	return ret;
}