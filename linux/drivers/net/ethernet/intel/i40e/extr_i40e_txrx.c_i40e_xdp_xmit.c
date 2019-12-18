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
typedef  int u32 ;
struct xdp_frame {int dummy; } ;
struct net_device {int dummy; } ;
struct i40e_vsi {unsigned int num_queue_pairs; struct i40e_ring** xdp_rings; int /*<<< orphan*/  state; struct i40e_pf* back; } ;
struct i40e_ring {int dummy; } ;
struct i40e_pf {int /*<<< orphan*/  state; } ;
struct i40e_netdev_priv {struct i40e_vsi* vsi; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENETDOWN ; 
 int ENXIO ; 
 int I40E_XDP_TX ; 
 int XDP_XMIT_FLAGS_MASK ; 
 int XDP_XMIT_FLUSH ; 
 int /*<<< orphan*/  __I40E_CONFIG_BUSY ; 
 int /*<<< orphan*/  __I40E_VSI_DOWN ; 
 int /*<<< orphan*/  i40e_enabled_xdp_vsi (struct i40e_vsi*) ; 
 int /*<<< orphan*/  i40e_xdp_ring_update_tail (struct i40e_ring*) ; 
 int i40e_xmit_xdp_ring (struct xdp_frame*,struct i40e_ring*) ; 
 struct i40e_netdev_priv* netdev_priv (struct net_device*) ; 
 unsigned int smp_processor_id () ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int) ; 
 int /*<<< orphan*/  xdp_return_frame_rx_napi (struct xdp_frame*) ; 

int i40e_xdp_xmit(struct net_device *dev, int n, struct xdp_frame **frames,
		  u32 flags)
{
	struct i40e_netdev_priv *np = netdev_priv(dev);
	unsigned int queue_index = smp_processor_id();
	struct i40e_vsi *vsi = np->vsi;
	struct i40e_pf *pf = vsi->back;
	struct i40e_ring *xdp_ring;
	int drops = 0;
	int i;

	if (test_bit(__I40E_VSI_DOWN, vsi->state))
		return -ENETDOWN;

	if (!i40e_enabled_xdp_vsi(vsi) || queue_index >= vsi->num_queue_pairs ||
	    test_bit(__I40E_CONFIG_BUSY, pf->state))
		return -ENXIO;

	if (unlikely(flags & ~XDP_XMIT_FLAGS_MASK))
		return -EINVAL;

	xdp_ring = vsi->xdp_rings[queue_index];

	for (i = 0; i < n; i++) {
		struct xdp_frame *xdpf = frames[i];
		int err;

		err = i40e_xmit_xdp_ring(xdpf, xdp_ring);
		if (err != I40E_XDP_TX) {
			xdp_return_frame_rx_napi(xdpf);
			drops++;
		}
	}

	if (unlikely(flags & XDP_XMIT_FLUSH))
		i40e_xdp_ring_update_tail(xdp_ring);

	return n - drops;
}