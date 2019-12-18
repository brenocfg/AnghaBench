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
union oid_res_t {int /*<<< orphan*/  u; } ;
struct net_device {int dummy; } ;
struct iw_request_info {int dummy; } ;
struct iw_freq {int e; int /*<<< orphan*/  m; int /*<<< orphan*/  i; } ;
typedef  int /*<<< orphan*/  islpci_private ;

/* Variables and functions */
 int /*<<< orphan*/  DOT11_OID_CHANNEL ; 
 int /*<<< orphan*/  DOT11_OID_FREQUENCY ; 
 int mgt_get_request (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,union oid_res_t*) ; 
 int /*<<< orphan*/ * netdev_priv (struct net_device*) ; 

__attribute__((used)) static int
prism54_get_freq(struct net_device *ndev, struct iw_request_info *info,
		 struct iw_freq *fwrq, char *extra)
{
	islpci_private *priv = netdev_priv(ndev);
	union oid_res_t r;
	int rvalue;

	rvalue = mgt_get_request(priv, DOT11_OID_CHANNEL, 0, NULL, &r);
	fwrq->i = r.u;
	rvalue |= mgt_get_request(priv, DOT11_OID_FREQUENCY, 0, NULL, &r);
	fwrq->m = r.u;
	fwrq->e = 3;

	return rvalue;
}