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
union oid_res_t {scalar_t__ u; } ;
struct net_device {int dummy; } ;
struct iw_request_info {int dummy; } ;
struct iw_param {int value; int fixed; scalar_t__ disabled; } ;
typedef  int s32 ;
typedef  int /*<<< orphan*/  islpci_private ;

/* Variables and functions */
 int /*<<< orphan*/  OID_INL_OUTPUTPOWER ; 
 int mgt_get_request (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,union oid_res_t*) ; 
 int /*<<< orphan*/ * netdev_priv (struct net_device*) ; 

__attribute__((used)) static int
prism54_get_txpower(struct net_device *ndev, struct iw_request_info *info,
		    struct iw_param *vwrq, char *extra)
{
	islpci_private *priv = netdev_priv(ndev);
	union oid_res_t r;
	int rvalue;

	rvalue = mgt_get_request(priv, OID_INL_OUTPUTPOWER, 0, NULL, &r);
	/* intersil firmware operates in 0.25 dBm (1/4 dBm) */
	vwrq->value = (s32) r.u / 4;
	vwrq->fixed = 1;
	/* radio is not turned of
	 * btw: how is possible to turn off only the radio
	 */
	vwrq->disabled = 0;

	return rvalue;
}