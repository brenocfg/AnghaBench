#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct tc_u32_sel {int nkeys; int offshift; TYPE_2__* keys; } ;
struct TYPE_7__ {int prio; int /*<<< orphan*/  protocol; } ;
struct TYPE_5__ {struct tc_u32_sel* sel; } ;
struct tc_cls_u32_offload {TYPE_3__ common; TYPE_1__ knode; } ;
struct TYPE_8__ {int match_en; int match_data; int frame_offset; } ;
struct stmmac_tc_entry {int prio; int is_frag; int in_use; TYPE_4__ val; struct stmmac_tc_entry* frag_ptr; } ;
struct stmmac_priv {int tc_off_max; } ;
struct TYPE_6__ {int off; int val; int mask; } ;

/* Variables and functions */
 int EINVAL ; 
 int ETH_HLEN ; 
#define  ETH_P_ALL 129 
#define  ETH_P_IP 128 
 int GENMASK (int,int) ; 
 int ntohs (int /*<<< orphan*/ ) ; 
 int tc_fill_actions (struct stmmac_tc_entry*,struct stmmac_tc_entry*,struct tc_cls_u32_offload*) ; 
 struct stmmac_tc_entry* tc_find_entry (struct stmmac_priv*,struct tc_cls_u32_offload*,int) ; 

__attribute__((used)) static int tc_fill_entry(struct stmmac_priv *priv,
			 struct tc_cls_u32_offload *cls)
{
	struct stmmac_tc_entry *entry, *frag = NULL;
	struct tc_u32_sel *sel = cls->knode.sel;
	u32 off, data, mask, real_off, rem;
	u32 prio = cls->common.prio << 16;
	int ret;

	/* Only 1 match per entry */
	if (sel->nkeys <= 0 || sel->nkeys > 1)
		return -EINVAL;

	off = sel->keys[0].off << sel->offshift;
	data = sel->keys[0].val;
	mask = sel->keys[0].mask;

	switch (ntohs(cls->common.protocol)) {
	case ETH_P_ALL:
		break;
	case ETH_P_IP:
		off += ETH_HLEN;
		break;
	default:
		return -EINVAL;
	}

	if (off > priv->tc_off_max)
		return -EINVAL;

	real_off = off / 4;
	rem = off % 4;

	entry = tc_find_entry(priv, cls, true);
	if (!entry)
		return -EINVAL;

	if (rem) {
		frag = tc_find_entry(priv, cls, true);
		if (!frag) {
			ret = -EINVAL;
			goto err_unuse;
		}

		entry->frag_ptr = frag;
		entry->val.match_en = (mask << (rem * 8)) &
			GENMASK(31, rem * 8);
		entry->val.match_data = (data << (rem * 8)) &
			GENMASK(31, rem * 8);
		entry->val.frame_offset = real_off;
		entry->prio = prio;

		frag->val.match_en = (mask >> (rem * 8)) &
			GENMASK(rem * 8 - 1, 0);
		frag->val.match_data = (data >> (rem * 8)) &
			GENMASK(rem * 8 - 1, 0);
		frag->val.frame_offset = real_off + 1;
		frag->prio = prio;
		frag->is_frag = true;
	} else {
		entry->frag_ptr = NULL;
		entry->val.match_en = mask;
		entry->val.match_data = data;
		entry->val.frame_offset = real_off;
		entry->prio = prio;
	}

	ret = tc_fill_actions(entry, frag, cls);
	if (ret)
		goto err_unuse;

	return 0;

err_unuse:
	if (frag)
		frag->in_use = false;
	entry->in_use = false;
	return ret;
}