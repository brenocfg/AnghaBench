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
struct xdp_frame {scalar_t__ len; } ;
struct net_device {int dummy; } ;
struct cpsw_priv {int dummy; } ;

/* Variables and functions */
 scalar_t__ CPSW_MIN_PACKET_SIZE ; 
 int EINVAL ; 
 int XDP_XMIT_FLAGS_MASK ; 
 scalar_t__ cpsw_xdp_tx_frame (struct cpsw_priv*,struct xdp_frame*,int /*<<< orphan*/ *) ; 
 struct cpsw_priv* netdev_priv (struct net_device*) ; 
 scalar_t__ unlikely (int) ; 
 int /*<<< orphan*/  xdp_return_frame_rx_napi (struct xdp_frame*) ; 

__attribute__((used)) static int cpsw_ndo_xdp_xmit(struct net_device *ndev, int n,
			     struct xdp_frame **frames, u32 flags)
{
	struct cpsw_priv *priv = netdev_priv(ndev);
	struct xdp_frame *xdpf;
	int i, drops = 0;

	if (unlikely(flags & ~XDP_XMIT_FLAGS_MASK))
		return -EINVAL;

	for (i = 0; i < n; i++) {
		xdpf = frames[i];
		if (xdpf->len < CPSW_MIN_PACKET_SIZE) {
			xdp_return_frame_rx_napi(xdpf);
			drops++;
			continue;
		}

		if (cpsw_xdp_tx_frame(priv, xdpf, NULL))
			drops++;
	}

	return n - drops;
}