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
struct r8152 {int /*<<< orphan*/  intf; int /*<<< orphan*/  control; int /*<<< orphan*/  flags; } ;
struct net_device {int dummy; } ;
struct mii_ioctl_data {int /*<<< orphan*/  val_in; int /*<<< orphan*/  reg_num; int /*<<< orphan*/  val_out; int /*<<< orphan*/  phy_id; } ;
struct ifreq {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CAP_NET_ADMIN ; 
 int ENODEV ; 
 int EOPNOTSUPP ; 
 int EPERM ; 
 int /*<<< orphan*/  R8152_PHY_ID ; 
 int /*<<< orphan*/  RTL8152_UNPLUG ; 
#define  SIOCGMIIPHY 130 
#define  SIOCGMIIREG 129 
#define  SIOCSMIIREG 128 
 int /*<<< orphan*/  capable (int /*<<< orphan*/ ) ; 
 struct mii_ioctl_data* if_mii (struct ifreq*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct r8152* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  r8152_mdio_read (struct r8152*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  r8152_mdio_write (struct r8152*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int usb_autopm_get_interface (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_autopm_put_interface (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int rtl8152_ioctl(struct net_device *netdev, struct ifreq *rq, int cmd)
{
	struct r8152 *tp = netdev_priv(netdev);
	struct mii_ioctl_data *data = if_mii(rq);
	int res;

	if (test_bit(RTL8152_UNPLUG, &tp->flags))
		return -ENODEV;

	res = usb_autopm_get_interface(tp->intf);
	if (res < 0)
		goto out;

	switch (cmd) {
	case SIOCGMIIPHY:
		data->phy_id = R8152_PHY_ID; /* Internal PHY */
		break;

	case SIOCGMIIREG:
		mutex_lock(&tp->control);
		data->val_out = r8152_mdio_read(tp, data->reg_num);
		mutex_unlock(&tp->control);
		break;

	case SIOCSMIIREG:
		if (!capable(CAP_NET_ADMIN)) {
			res = -EPERM;
			break;
		}
		mutex_lock(&tp->control);
		r8152_mdio_write(tp, data->reg_num, data->val_in);
		mutex_unlock(&tp->control);
		break;

	default:
		res = -EOPNOTSUPP;
	}

	usb_autopm_put_interface(tp->intf);

out:
	return res;
}