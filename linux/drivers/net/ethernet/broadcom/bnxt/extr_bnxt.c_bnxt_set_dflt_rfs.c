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
struct net_device {int /*<<< orphan*/  features; int /*<<< orphan*/  hw_features; } ;
struct bnxt {int /*<<< orphan*/  flags; struct net_device* dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  BNXT_FLAG_RFS ; 
 int /*<<< orphan*/  NETIF_F_NTUPLE ; 
 scalar_t__ bnxt_rfs_capable (struct bnxt*) ; 
 scalar_t__ bnxt_rfs_supported (struct bnxt*) ; 

__attribute__((used)) static void bnxt_set_dflt_rfs(struct bnxt *bp)
{
	struct net_device *dev = bp->dev;

	dev->hw_features &= ~NETIF_F_NTUPLE;
	dev->features &= ~NETIF_F_NTUPLE;
	bp->flags &= ~BNXT_FLAG_RFS;
	if (bnxt_rfs_supported(bp)) {
		dev->hw_features |= NETIF_F_NTUPLE;
		if (bnxt_rfs_capable(bp)) {
			bp->flags |= BNXT_FLAG_RFS;
			dev->features |= NETIF_F_NTUPLE;
		}
	}
}