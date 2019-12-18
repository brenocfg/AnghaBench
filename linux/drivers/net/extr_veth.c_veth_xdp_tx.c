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
struct xdp_frame {int dummy; } ;
struct xdp_buff {int dummy; } ;
struct veth_xdp_tx_bq {scalar_t__ count; struct xdp_frame** q; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 int EOVERFLOW ; 
 scalar_t__ VETH_XDP_TX_BULK_SIZE ; 
 struct xdp_frame* convert_to_xdp_frame (struct xdp_buff*) ; 
 scalar_t__ unlikely (int) ; 
 int /*<<< orphan*/  veth_xdp_flush_bq (struct net_device*,struct veth_xdp_tx_bq*) ; 

__attribute__((used)) static int veth_xdp_tx(struct net_device *dev, struct xdp_buff *xdp,
		       struct veth_xdp_tx_bq *bq)
{
	struct xdp_frame *frame = convert_to_xdp_frame(xdp);

	if (unlikely(!frame))
		return -EOVERFLOW;

	if (unlikely(bq->count == VETH_XDP_TX_BULK_SIZE))
		veth_xdp_flush_bq(dev, bq);

	bq->q[bq->count++] = frame;

	return 0;
}