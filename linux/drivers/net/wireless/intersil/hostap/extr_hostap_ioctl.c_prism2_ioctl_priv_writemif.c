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
typedef  char u16 ;
struct net_device {int dummy; } ;
struct iw_request_info {int dummy; } ;
struct hostap_interface {TYPE_2__* local; } ;
struct TYPE_4__ {TYPE_1__* func; } ;
typedef  TYPE_2__ local_info_t ;
struct TYPE_3__ {scalar_t__ (* cmd ) (struct net_device*,int /*<<< orphan*/ ,char,char*,int /*<<< orphan*/ *) ;} ;

/* Variables and functions */
 int EOPNOTSUPP ; 
 int /*<<< orphan*/  HFA384X_CMDCODE_WRITEMIF ; 
 struct hostap_interface* netdev_priv (struct net_device*) ; 
 scalar_t__ stub1 (struct net_device*,int /*<<< orphan*/ ,char,char*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int prism2_ioctl_priv_writemif(struct net_device *dev,
				      struct iw_request_info *info,
				      void *wrqu, char *extra)
{
	struct hostap_interface *iface;
	local_info_t *local;
	u16 cr, val;

	iface = netdev_priv(dev);
	local = iface->local;

	cr = *extra;
	val = *(extra + 1);
	if (local->func->cmd(dev, HFA384X_CMDCODE_WRITEMIF, cr, &val, NULL))
		return -EOPNOTSUPP;

	return 0;
}