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
struct bnxt {int flags; int /*<<< orphan*/  rx_skb_func; int /*<<< orphan*/  rx_dir; int /*<<< orphan*/  max_mtu; TYPE_1__* dev; } ;
struct TYPE_2__ {scalar_t__ mtu; int /*<<< orphan*/  max_mtu; } ;

/* Variables and functions */
 int BNXT_FLAG_AGG_RINGS ; 
 int BNXT_FLAG_NO_AGG_RINGS ; 
 int BNXT_FLAG_RX_PAGE_MODE ; 
 scalar_t__ BNXT_MAX_PAGE_MODE_MTU ; 
 int /*<<< orphan*/  DMA_BIDIRECTIONAL ; 
 int /*<<< orphan*/  DMA_FROM_DEVICE ; 
 int EOPNOTSUPP ; 
 int /*<<< orphan*/  bnxt_rx_page_skb ; 
 int /*<<< orphan*/  bnxt_rx_skb ; 
 int /*<<< orphan*/  min_t (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  netdev_update_features (TYPE_1__*) ; 
 int /*<<< orphan*/  u16 ; 

int bnxt_set_rx_skb_mode(struct bnxt *bp, bool page_mode)
{
	if (page_mode) {
		if (bp->dev->mtu > BNXT_MAX_PAGE_MODE_MTU)
			return -EOPNOTSUPP;
		bp->dev->max_mtu =
			min_t(u16, bp->max_mtu, BNXT_MAX_PAGE_MODE_MTU);
		bp->flags &= ~BNXT_FLAG_AGG_RINGS;
		bp->flags |= BNXT_FLAG_NO_AGG_RINGS | BNXT_FLAG_RX_PAGE_MODE;
		bp->rx_dir = DMA_BIDIRECTIONAL;
		bp->rx_skb_func = bnxt_rx_page_skb;
		/* Disable LRO or GRO_HW */
		netdev_update_features(bp->dev);
	} else {
		bp->dev->max_mtu = bp->max_mtu;
		bp->flags &= ~BNXT_FLAG_RX_PAGE_MODE;
		bp->rx_dir = DMA_FROM_DEVICE;
		bp->rx_skb_func = bnxt_rx_skb;
	}
	return 0;
}