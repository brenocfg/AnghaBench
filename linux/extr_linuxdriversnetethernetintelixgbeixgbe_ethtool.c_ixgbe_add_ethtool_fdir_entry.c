#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_21__   TYPE_9__ ;
typedef  struct TYPE_20__   TYPE_8__ ;
typedef  struct TYPE_19__   TYPE_7__ ;
typedef  struct TYPE_18__   TYPE_6__ ;
typedef  struct TYPE_17__   TYPE_5__ ;
typedef  struct TYPE_16__   TYPE_4__ ;
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;
typedef  struct TYPE_12__   TYPE_10__ ;

/* Type definitions */
struct TYPE_20__ {int flow_type; unsigned char vm_pool; int /*<<< orphan*/  flex_bytes; int /*<<< orphan*/  vlan_id; int /*<<< orphan*/  dst_port; int /*<<< orphan*/  src_port; int /*<<< orphan*/ * dst_ip; int /*<<< orphan*/ * src_ip; } ;
union ixgbe_atr_input {TYPE_8__ formatted; } ;
typedef  int u8 ;
typedef  size_t u32 ;
struct ixgbe_hw {int dummy; } ;
struct TYPE_18__ {scalar_t__ flow_type; unsigned char vm_pool; int /*<<< orphan*/  flex_bytes; int /*<<< orphan*/  vlan_id; int /*<<< orphan*/  dst_port; int /*<<< orphan*/  src_port; int /*<<< orphan*/ * dst_ip; int /*<<< orphan*/ * src_ip; } ;
struct TYPE_12__ {TYPE_6__ formatted; } ;
struct ixgbe_fdir_filter {int sw_idx; scalar_t__ action; TYPE_10__ filter; } ;
struct ixgbe_adapter {int flags; size_t num_rx_queues; int num_vfs; size_t num_rx_queues_per_pool; int fdir_pballoc; int /*<<< orphan*/  fdir_perfect_lock; int /*<<< orphan*/  fdir_mask; int /*<<< orphan*/  fdir_filter_list; TYPE_1__** rx_ring; struct ixgbe_hw hw; } ;
struct ethtool_rxnfc {int /*<<< orphan*/  fs; } ;
struct TYPE_21__ {int /*<<< orphan*/  vlan_etype; int /*<<< orphan*/  vlan_tci; int /*<<< orphan*/ * data; } ;
struct TYPE_19__ {int /*<<< orphan*/  vlan_etype; int /*<<< orphan*/  vlan_tci; int /*<<< orphan*/ * data; } ;
struct TYPE_16__ {int /*<<< orphan*/  pdst; int /*<<< orphan*/  psrc; int /*<<< orphan*/  ip4dst; int /*<<< orphan*/  ip4src; } ;
struct TYPE_17__ {TYPE_4__ tcp_ip4_spec; } ;
struct TYPE_14__ {int /*<<< orphan*/  pdst; int /*<<< orphan*/  psrc; int /*<<< orphan*/  ip4dst; int /*<<< orphan*/  ip4src; } ;
struct TYPE_15__ {TYPE_2__ tcp_ip4_spec; } ;
struct ethtool_rx_flow_spec {scalar_t__ ring_cookie; int location; int flow_type; TYPE_9__ m_ext; TYPE_7__ h_ext; TYPE_5__ m_u; TYPE_3__ h_u; } ;
typedef  int /*<<< orphan*/  mask ;
struct TYPE_13__ {int reg_idx; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int EOPNOTSUPP ; 
 int FLOW_EXT ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 scalar_t__ IXGBE_ATR_FLOW_TYPE_IPV4 ; 
 int IXGBE_ATR_L4TYPE_IPV6_MASK ; 
 int IXGBE_ATR_L4TYPE_MASK ; 
 void* IXGBE_FDIR_DROP_QUEUE ; 
 int IXGBE_FLAG_FDIR_PERFECT_CAPABLE ; 
 scalar_t__ RX_CLS_FLOW_DISC ; 
 int /*<<< orphan*/  drv ; 
 int /*<<< orphan*/  e_err (int /*<<< orphan*/ ,char*) ; 
 size_t ethtool_get_flow_spec_ring (scalar_t__) ; 
 int ethtool_get_flow_spec_ring_vf (scalar_t__) ; 
 scalar_t__ hlist_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ixgbe_atr_compute_perfect_hash_82599 (TYPE_10__*,union ixgbe_atr_input*) ; 
 int ixgbe_fdir_set_input_mask_82599 (struct ixgbe_hw*,union ixgbe_atr_input*) ; 
 int ixgbe_fdir_write_perfect_filter_82599 (struct ixgbe_hw*,TYPE_10__*,int,int) ; 
 int /*<<< orphan*/  ixgbe_flowspec_to_flow_type (struct ethtool_rx_flow_spec*,scalar_t__*) ; 
 int /*<<< orphan*/  ixgbe_update_ethtool_fdir_entry (struct ixgbe_adapter*,struct ixgbe_fdir_filter*,int) ; 
 int /*<<< orphan*/  kfree (struct ixgbe_fdir_filter*) ; 
 struct ixgbe_fdir_filter* kzalloc (int,int /*<<< orphan*/ ) ; 
 scalar_t__ memcmp (int /*<<< orphan*/ *,union ixgbe_atr_input*,int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,union ixgbe_atr_input*,int) ; 
 int /*<<< orphan*/  memset (union ixgbe_atr_input*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ ntohl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int ixgbe_add_ethtool_fdir_entry(struct ixgbe_adapter *adapter,
					struct ethtool_rxnfc *cmd)
{
	struct ethtool_rx_flow_spec *fsp =
		(struct ethtool_rx_flow_spec *)&cmd->fs;
	struct ixgbe_hw *hw = &adapter->hw;
	struct ixgbe_fdir_filter *input;
	union ixgbe_atr_input mask;
	u8 queue;
	int err;

	if (!(adapter->flags & IXGBE_FLAG_FDIR_PERFECT_CAPABLE))
		return -EOPNOTSUPP;

	/* ring_cookie is a masked into a set of queues and ixgbe pools or
	 * we use the drop index.
	 */
	if (fsp->ring_cookie == RX_CLS_FLOW_DISC) {
		queue = IXGBE_FDIR_DROP_QUEUE;
	} else {
		u32 ring = ethtool_get_flow_spec_ring(fsp->ring_cookie);
		u8 vf = ethtool_get_flow_spec_ring_vf(fsp->ring_cookie);

		if (!vf && (ring >= adapter->num_rx_queues))
			return -EINVAL;
		else if (vf &&
			 ((vf > adapter->num_vfs) ||
			   ring >= adapter->num_rx_queues_per_pool))
			return -EINVAL;

		/* Map the ring onto the absolute queue index */
		if (!vf)
			queue = adapter->rx_ring[ring]->reg_idx;
		else
			queue = ((vf - 1) *
				adapter->num_rx_queues_per_pool) + ring;
	}

	/* Don't allow indexes to exist outside of available space */
	if (fsp->location >= ((1024 << adapter->fdir_pballoc) - 2)) {
		e_err(drv, "Location out of range\n");
		return -EINVAL;
	}

	input = kzalloc(sizeof(*input), GFP_ATOMIC);
	if (!input)
		return -ENOMEM;

	memset(&mask, 0, sizeof(union ixgbe_atr_input));

	/* set SW index */
	input->sw_idx = fsp->location;

	/* record flow type */
	if (!ixgbe_flowspec_to_flow_type(fsp,
					 &input->filter.formatted.flow_type)) {
		e_err(drv, "Unrecognized flow type\n");
		goto err_out;
	}

	mask.formatted.flow_type = IXGBE_ATR_L4TYPE_IPV6_MASK |
				   IXGBE_ATR_L4TYPE_MASK;

	if (input->filter.formatted.flow_type == IXGBE_ATR_FLOW_TYPE_IPV4)
		mask.formatted.flow_type &= IXGBE_ATR_L4TYPE_IPV6_MASK;

	/* Copy input into formatted structures */
	input->filter.formatted.src_ip[0] = fsp->h_u.tcp_ip4_spec.ip4src;
	mask.formatted.src_ip[0] = fsp->m_u.tcp_ip4_spec.ip4src;
	input->filter.formatted.dst_ip[0] = fsp->h_u.tcp_ip4_spec.ip4dst;
	mask.formatted.dst_ip[0] = fsp->m_u.tcp_ip4_spec.ip4dst;
	input->filter.formatted.src_port = fsp->h_u.tcp_ip4_spec.psrc;
	mask.formatted.src_port = fsp->m_u.tcp_ip4_spec.psrc;
	input->filter.formatted.dst_port = fsp->h_u.tcp_ip4_spec.pdst;
	mask.formatted.dst_port = fsp->m_u.tcp_ip4_spec.pdst;

	if (fsp->flow_type & FLOW_EXT) {
		input->filter.formatted.vm_pool =
				(unsigned char)ntohl(fsp->h_ext.data[1]);
		mask.formatted.vm_pool =
				(unsigned char)ntohl(fsp->m_ext.data[1]);
		input->filter.formatted.vlan_id = fsp->h_ext.vlan_tci;
		mask.formatted.vlan_id = fsp->m_ext.vlan_tci;
		input->filter.formatted.flex_bytes =
						fsp->h_ext.vlan_etype;
		mask.formatted.flex_bytes = fsp->m_ext.vlan_etype;
	}

	/* determine if we need to drop or route the packet */
	if (fsp->ring_cookie == RX_CLS_FLOW_DISC)
		input->action = IXGBE_FDIR_DROP_QUEUE;
	else
		input->action = fsp->ring_cookie;

	spin_lock(&adapter->fdir_perfect_lock);

	if (hlist_empty(&adapter->fdir_filter_list)) {
		/* save mask and program input mask into HW */
		memcpy(&adapter->fdir_mask, &mask, sizeof(mask));
		err = ixgbe_fdir_set_input_mask_82599(hw, &mask);
		if (err) {
			e_err(drv, "Error writing mask\n");
			goto err_out_w_lock;
		}
	} else if (memcmp(&adapter->fdir_mask, &mask, sizeof(mask))) {
		e_err(drv, "Only one mask supported per port\n");
		goto err_out_w_lock;
	}

	/* apply mask and compute/store hash */
	ixgbe_atr_compute_perfect_hash_82599(&input->filter, &mask);

	/* program filters to filter memory */
	err = ixgbe_fdir_write_perfect_filter_82599(hw,
				&input->filter, input->sw_idx, queue);
	if (err)
		goto err_out_w_lock;

	ixgbe_update_ethtool_fdir_entry(adapter, input, input->sw_idx);

	spin_unlock(&adapter->fdir_perfect_lock);

	return err;
err_out_w_lock:
	spin_unlock(&adapter->fdir_perfect_lock);
err_out:
	kfree(input);
	return -EINVAL;
}