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
struct zd1201 {int dummy; } ;
struct net_device {int dummy; } ;
struct iw_request_info {int dummy; } ;
struct iw_param {int value; scalar_t__ disabled; scalar_t__ fixed; } ;

/* Variables and functions */
 int /*<<< orphan*/  ZD1201_RID_CURRENTTXRATE ; 
 struct zd1201* netdev_priv (struct net_device*) ; 
 int zd1201_getconfig16 (struct zd1201*,int /*<<< orphan*/ ,short*) ; 

__attribute__((used)) static int zd1201_get_rate(struct net_device *dev,
    struct iw_request_info *info, struct iw_param *rrq, char *extra)
{
	struct zd1201 *zd = netdev_priv(dev);
	short rate;
	int err;

	err = zd1201_getconfig16(zd, ZD1201_RID_CURRENTTXRATE, &rate);
	if (err)
		return err;

	switch(rate) {
		case 1:
			rrq->value = 1000000;
			break;
		case 2:
			rrq->value = 2000000;
			break;
		case 5:
			rrq->value = 5500000;
			break;
		case 11:
			rrq->value = 11000000;
			break;
		default:
			rrq->value = 0;
	}
	rrq->fixed = 0;
	rrq->disabled = 0;

	return 0;
}