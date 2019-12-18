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
struct iw_param {int fixed; int value; } ;
struct atmel_private {int tx_rate; scalar_t__ auto_tx_rate; } ;

/* Variables and functions */
 struct atmel_private* netdev_priv (struct net_device*) ; 

__attribute__((used)) static int atmel_get_rate(struct net_device *dev,
			 struct iw_request_info *info,
			 struct iw_param *vwrq,
			 char *extra)
{
	struct atmel_private *priv = netdev_priv(dev);

	if (priv->auto_tx_rate) {
		vwrq->fixed = 0;
		vwrq->value = 11000000;
	} else {
		vwrq->fixed = 1;
		switch (priv->tx_rate) {
		case 0:
			vwrq->value =  1000000;
			break;
		case 1:
			vwrq->value =  2000000;
			break;
		case 2:
			vwrq->value =  5500000;
			break;
		case 3:
			vwrq->value = 11000000;
			break;
		}
	}
	return 0;
}