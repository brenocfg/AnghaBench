#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_8__ ;
typedef  struct TYPE_15__   TYPE_7__ ;
typedef  struct TYPE_14__   TYPE_6__ ;
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct TYPE_15__ {int handle; int link_handle; TYPE_6__* sel; } ;
struct TYPE_11__ {scalar_t__ protocol; } ;
struct tc_cls_u32_offload {TYPE_7__ knode; TYPE_3__ common; } ;
struct net_device {int dummy; } ;
struct cxgb4_tc_u32_table {int size; struct cxgb4_link* table; } ;
struct cxgb4_next_header {scalar_t__ offoff; scalar_t__ shift; scalar_t__ mask; scalar_t__ offset; int match_off; int match_val; int match_mask; struct cxgb4_match_field* jump; } ;
struct cxgb4_match_field {int dummy; } ;
struct TYPE_10__ {int /*<<< orphan*/  iport; } ;
struct TYPE_9__ {int /*<<< orphan*/  iport; } ;
struct ch_filter_specification {int hitcnts; int type; TYPE_2__ mask; TYPE_1__ val; } ;
struct cxgb4_link {int link_handle; int /*<<< orphan*/  tid_map; struct ch_filter_specification fs; struct cxgb4_match_field* match_field; } ;
struct TYPE_12__ {unsigned int nftids; } ;
struct adapter {int /*<<< orphan*/  pdev_dev; struct cxgb4_tc_u32_table* tc_u32; TYPE_4__ tids; } ;
typedef  int /*<<< orphan*/  fs ;
typedef  scalar_t__ __be16 ;
struct TYPE_16__ {int /*<<< orphan*/  port_id; } ;
struct TYPE_14__ {scalar_t__ offoff; scalar_t__ offshift; scalar_t__ offmask; scalar_t__ off; unsigned int nkeys; TYPE_5__* keys; } ;
struct TYPE_13__ {int off; int val; int mask; } ;

/* Variables and functions */
 int EINVAL ; 
 int EOPNOTSUPP ; 
 int ERANGE ; 
 int /*<<< orphan*/  ETH_P_IP ; 
 int /*<<< orphan*/  ETH_P_IPV6 ; 
 int TC_U32_USERHTID (int) ; 
 int /*<<< orphan*/  can_tc_u32_offload (struct net_device*) ; 
 struct cxgb4_match_field* cxgb4_ipv4_fields ; 
 struct cxgb4_next_header* cxgb4_ipv4_jumps ; 
 struct cxgb4_match_field* cxgb4_ipv6_fields ; 
 struct cxgb4_next_header* cxgb4_ipv6_jumps ; 
 int cxgb4_set_filter (struct net_device*,unsigned int,struct ch_filter_specification*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int,...) ; 
 int fill_action_fields (struct adapter*,struct ch_filter_specification*,struct tc_cls_u32_offload*) ; 
 int fill_match_fields (struct adapter*,struct ch_filter_specification*,struct tc_cls_u32_offload*,struct cxgb4_match_field const*,int) ; 
 scalar_t__ htons (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (struct ch_filter_specification*,struct ch_filter_specification*,int) ; 
 int /*<<< orphan*/  memset (struct ch_filter_specification*,int /*<<< orphan*/ ,int) ; 
 struct adapter* netdev2adap (struct net_device*) ; 
 TYPE_8__* netdev2pinfo (struct net_device*) ; 
 int /*<<< orphan*/  set_bit (unsigned int,int /*<<< orphan*/ ) ; 

int cxgb4_config_knode(struct net_device *dev, struct tc_cls_u32_offload *cls)
{
	const struct cxgb4_match_field *start, *link_start = NULL;
	struct adapter *adapter = netdev2adap(dev);
	__be16 protocol = cls->common.protocol;
	struct ch_filter_specification fs;
	struct cxgb4_tc_u32_table *t;
	struct cxgb4_link *link;
	unsigned int filter_id;
	u32 uhtid, link_uhtid;
	bool is_ipv6 = false;
	int ret;

	if (!can_tc_u32_offload(dev))
		return -EOPNOTSUPP;

	if (protocol != htons(ETH_P_IP) && protocol != htons(ETH_P_IPV6))
		return -EOPNOTSUPP;

	/* Fetch the location to insert the filter. */
	filter_id = cls->knode.handle & 0xFFFFF;

	if (filter_id > adapter->tids.nftids) {
		dev_err(adapter->pdev_dev,
			"Location %d out of range for insertion. Max: %d\n",
			filter_id, adapter->tids.nftids);
		return -ERANGE;
	}

	t = adapter->tc_u32;
	uhtid = TC_U32_USERHTID(cls->knode.handle);
	link_uhtid = TC_U32_USERHTID(cls->knode.link_handle);

	/* Ensure that uhtid is either root u32 (i.e. 0x800)
	 * or a a valid linked bucket.
	 */
	if (uhtid != 0x800 && uhtid >= t->size)
		return -EINVAL;

	/* Ensure link handle uhtid is sane, if specified. */
	if (link_uhtid >= t->size)
		return -EINVAL;

	memset(&fs, 0, sizeof(fs));

	if (protocol == htons(ETH_P_IPV6)) {
		start = cxgb4_ipv6_fields;
		is_ipv6 = true;
	} else {
		start = cxgb4_ipv4_fields;
		is_ipv6 = false;
	}

	if (uhtid != 0x800) {
		/* Link must exist from root node before insertion. */
		if (!t->table[uhtid - 1].link_handle)
			return -EINVAL;

		/* Link must have a valid supported next header. */
		link_start = t->table[uhtid - 1].match_field;
		if (!link_start)
			return -EINVAL;
	}

	/* Parse links and record them for subsequent jumps to valid
	 * next headers.
	 */
	if (link_uhtid) {
		const struct cxgb4_next_header *next;
		bool found = false;
		unsigned int i, j;
		u32 val, mask;
		int off;

		if (t->table[link_uhtid - 1].link_handle) {
			dev_err(adapter->pdev_dev,
				"Link handle exists for: 0x%x\n",
				link_uhtid);
			return -EINVAL;
		}

		next = is_ipv6 ? cxgb4_ipv6_jumps : cxgb4_ipv4_jumps;

		/* Try to find matches that allow jumps to next header. */
		for (i = 0; next[i].jump; i++) {
			if (next[i].offoff != cls->knode.sel->offoff ||
			    next[i].shift != cls->knode.sel->offshift ||
			    next[i].mask != cls->knode.sel->offmask ||
			    next[i].offset != cls->knode.sel->off)
				continue;

			/* Found a possible candidate.  Find a key that
			 * matches the corresponding offset, value, and
			 * mask to jump to next header.
			 */
			for (j = 0; j < cls->knode.sel->nkeys; j++) {
				off = cls->knode.sel->keys[j].off;
				val = cls->knode.sel->keys[j].val;
				mask = cls->knode.sel->keys[j].mask;

				if (next[i].match_off == off &&
				    next[i].match_val == val &&
				    next[i].match_mask == mask) {
					found = true;
					break;
				}
			}

			if (!found)
				continue; /* Try next candidate. */

			/* Candidate to jump to next header found.
			 * Translate all keys to internal specification
			 * and store them in jump table. This spec is copied
			 * later to set the actual filters.
			 */
			ret = fill_match_fields(adapter, &fs, cls,
						start, false);
			if (ret)
				goto out;

			link = &t->table[link_uhtid - 1];
			link->match_field = next[i].jump;
			link->link_handle = cls->knode.handle;
			memcpy(&link->fs, &fs, sizeof(fs));
			break;
		}

		/* No candidate found to jump to next header. */
		if (!found)
			return -EINVAL;

		return 0;
	}

	/* Fill ch_filter_specification match fields to be shipped to hardware.
	 * Copy the linked spec (if any) first.  And then update the spec as
	 * needed.
	 */
	if (uhtid != 0x800 && t->table[uhtid - 1].link_handle) {
		/* Copy linked ch_filter_specification */
		memcpy(&fs, &t->table[uhtid - 1].fs, sizeof(fs));
		ret = fill_match_fields(adapter, &fs, cls,
					link_start, true);
		if (ret)
			goto out;
	}

	ret = fill_match_fields(adapter, &fs, cls, start, false);
	if (ret)
		goto out;

	/* Fill ch_filter_specification action fields to be shipped to
	 * hardware.
	 */
	ret = fill_action_fields(adapter, &fs, cls);
	if (ret)
		goto out;

	/* The filter spec has been completely built from the info
	 * provided from u32.  We now set some default fields in the
	 * spec for sanity.
	 */

	/* Match only packets coming from the ingress port where this
	 * filter will be created.
	 */
	fs.val.iport = netdev2pinfo(dev)->port_id;
	fs.mask.iport = ~0;

	/* Enable filter hit counts. */
	fs.hitcnts = 1;

	/* Set type of filter - IPv6 or IPv4 */
	fs.type = is_ipv6 ? 1 : 0;

	/* Set the filter */
	ret = cxgb4_set_filter(dev, filter_id, &fs);
	if (ret)
		goto out;

	/* If this is a linked bucket, then set the corresponding
	 * entry in the bitmap to mark it as belonging to this linked
	 * bucket.
	 */
	if (uhtid != 0x800 && t->table[uhtid - 1].link_handle)
		set_bit(filter_id, t->table[uhtid - 1].tid_map);

out:
	return ret;
}