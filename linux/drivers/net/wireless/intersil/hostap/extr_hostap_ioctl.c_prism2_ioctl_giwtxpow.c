#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u16 ;
struct net_device {int dummy; } ;
struct iw_request_info {int dummy; } ;
struct iw_param {int disabled; int fixed; int value; int /*<<< orphan*/  flags; } ;
struct hostap_interface {TYPE_2__* local; } ;
struct TYPE_4__ {scalar_t__ txpower_type; int txpower; TYPE_1__* func; } ;
typedef  TYPE_2__ local_info_t ;
struct TYPE_3__ {scalar_t__ (* cmd ) (struct net_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ;} ;

/* Variables and functions */
 int EOPNOTSUPP ; 
 int /*<<< orphan*/  HFA384X_CMDCODE_READMIF ; 
 int /*<<< orphan*/  HFA386X_CR_MANUAL_TX_POWER ; 
 int /*<<< orphan*/  IW_TXPOW_DBM ; 
 scalar_t__ PRISM2_TXPOWER_AUTO ; 
 scalar_t__ PRISM2_TXPOWER_FIXED ; 
 scalar_t__ PRISM2_TXPOWER_OFF ; 
 struct hostap_interface* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  printk (char*,scalar_t__) ; 
 int prism2_txpower_hfa386x_to_dBm (int /*<<< orphan*/ ) ; 
 scalar_t__ stub1 (struct net_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int prism2_ioctl_giwtxpow(struct net_device *dev,
				 struct iw_request_info *info,
				 struct iw_param *rrq, char *extra)
{
#ifdef RAW_TXPOWER_SETTING
	struct hostap_interface *iface;
	local_info_t *local;
	u16 resp0;

	iface = netdev_priv(dev);
	local = iface->local;

	rrq->flags = IW_TXPOW_DBM;
	rrq->disabled = 0;
	rrq->fixed = 0;

	if (local->txpower_type == PRISM2_TXPOWER_AUTO) {
		if (local->func->cmd(dev, HFA384X_CMDCODE_READMIF,
				     HFA386X_CR_MANUAL_TX_POWER,
				     NULL, &resp0) == 0) {
			rrq->value = prism2_txpower_hfa386x_to_dBm(resp0);
		} else {
			/* Could not get real txpower; guess 15 dBm */
			rrq->value = 15;
		}
	} else if (local->txpower_type == PRISM2_TXPOWER_OFF) {
		rrq->value = 0;
		rrq->disabled = 1;
	} else if (local->txpower_type == PRISM2_TXPOWER_FIXED) {
		rrq->value = local->txpower;
		rrq->fixed = 1;
	} else {
		printk("SIOCGIWTXPOW - unknown txpower_type=%d\n",
		       local->txpower_type);
	}
	return 0;
#else /* RAW_TXPOWER_SETTING */
	return -EOPNOTSUPP;
#endif /* RAW_TXPOWER_SETTING */
}