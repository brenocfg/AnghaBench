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
struct net_device {int /*<<< orphan*/  features; } ;
struct macb {struct net_device* dev; } ;
typedef  int /*<<< orphan*/  netdev_features_t ;

/* Variables and functions */
 int /*<<< orphan*/  macb_set_rxcsum_feature (struct macb*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  macb_set_rxflow_feature (struct macb*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  macb_set_txcsum_feature (struct macb*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void macb_restore_features(struct macb *bp)
{
	struct net_device *netdev = bp->dev;
	netdev_features_t features = netdev->features;

	/* TX checksum offload */
	macb_set_txcsum_feature(bp, features);

	/* RX checksum offload */
	macb_set_rxcsum_feature(bp, features);

	/* RX Flow Filters */
	macb_set_rxflow_feature(bp, features);
}