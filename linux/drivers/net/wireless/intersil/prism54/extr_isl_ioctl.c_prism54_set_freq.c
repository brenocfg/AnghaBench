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
struct net_device {int dummy; } ;
struct iw_request_info {int dummy; } ;
struct iw_freq {int m; int e; } ;
typedef  int /*<<< orphan*/  islpci_private ;

/* Variables and functions */
 int /*<<< orphan*/  DOT11_OID_CHANNEL ; 
 int EINPROGRESS ; 
 int EINVAL ; 
 int channel_of_freq (int) ; 
 int mgt_set_request (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/ * netdev_priv (struct net_device*) ; 

__attribute__((used)) static int
prism54_set_freq(struct net_device *ndev, struct iw_request_info *info,
		 struct iw_freq *fwrq, char *extra)
{
	islpci_private *priv = netdev_priv(ndev);
	int rvalue;
	u32 c;

	if (fwrq->m < 1000)
		/* we have a channel number */
		c = fwrq->m;
	else
		c = (fwrq->e == 1) ? channel_of_freq(fwrq->m / 100000) : 0;

	rvalue = c ? mgt_set_request(priv, DOT11_OID_CHANNEL, 0, &c) : -EINVAL;

	/* Call commit handler */
	return (rvalue ? rvalue : -EINPROGRESS);
}