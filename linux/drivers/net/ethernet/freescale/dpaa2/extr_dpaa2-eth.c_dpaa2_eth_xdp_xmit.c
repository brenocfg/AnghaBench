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

/* Variables and functions */
 int EINVAL ; 
 int ENETDOWN ; 
 int XDP_XMIT_FLAGS_MASK ; 
 int dpaa2_eth_xdp_xmit_frame (struct net_device*,struct xdp_frame*) ; 
 int /*<<< orphan*/  netif_running (struct net_device*) ; 
 scalar_t__ unlikely (int) ; 
 int /*<<< orphan*/  xdp_return_frame_rx_napi (struct xdp_frame*) ; 

__attribute__((used)) static int dpaa2_eth_xdp_xmit(struct net_device *net_dev, int n,
			      struct xdp_frame **frames, u32 flags)
{
	int drops = 0;
	int i, err;

	if (unlikely(flags & ~XDP_XMIT_FLAGS_MASK))
		return -EINVAL;

	if (!netif_running(net_dev))
		return -ENETDOWN;

	for (i = 0; i < n; i++) {
		struct xdp_frame *xdpf = frames[i];

		err = dpaa2_eth_xdp_xmit_frame(net_dev, xdpf);
		if (err) {
			xdp_return_frame_rx_napi(xdpf);
			drops++;
		}
	}

	return n - drops;
}