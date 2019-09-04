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
struct net_device {int dummy; } ;
struct bnxt {int dummy; } ;

/* Variables and functions */
 int __bnxt_open_nic (struct bnxt*,int,int) ; 
 int /*<<< orphan*/  bnxt_hwmon_open (struct bnxt*) ; 
 int /*<<< orphan*/  bnxt_hwrm_if_change (struct bnxt*,int) ; 
 struct bnxt* netdev_priv (struct net_device*) ; 

__attribute__((used)) static int bnxt_open(struct net_device *dev)
{
	struct bnxt *bp = netdev_priv(dev);
	int rc;

	bnxt_hwrm_if_change(bp, true);
	rc = __bnxt_open_nic(bp, true, true);
	if (rc)
		bnxt_hwrm_if_change(bp, false);

	bnxt_hwmon_open(bp);

	return rc;
}