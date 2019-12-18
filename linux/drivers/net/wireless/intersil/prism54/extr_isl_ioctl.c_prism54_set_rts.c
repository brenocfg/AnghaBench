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
struct iw_request_info {int dummy; } ;
struct iw_param {int /*<<< orphan*/  value; } ;
typedef  int /*<<< orphan*/  islpci_private ;

/* Variables and functions */
 int /*<<< orphan*/  DOT11_OID_RTSTHRESH ; 
 int mgt_set_request (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * netdev_priv (struct net_device*) ; 

__attribute__((used)) static int
prism54_set_rts(struct net_device *ndev, struct iw_request_info *info,
		struct iw_param *vwrq, char *extra)
{
	islpci_private *priv = netdev_priv(ndev);

	return mgt_set_request(priv, DOT11_OID_RTSTHRESH, 0, &vwrq->value);
}