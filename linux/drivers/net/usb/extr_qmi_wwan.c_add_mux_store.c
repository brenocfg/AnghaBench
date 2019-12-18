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
typedef  int u8 ;
struct usbnet {int /*<<< orphan*/  net; int /*<<< orphan*/  data; } ;
struct qmi_wwan_state {int /*<<< orphan*/  flags; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int ssize_t ;

/* Variables and functions */
 int EBUSY ; 
 int EINVAL ; 
 int /*<<< orphan*/  QMI_WWAN_FLAG_MUX ; 
 scalar_t__ kstrtou8 (char const*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  netdev_err (int /*<<< orphan*/ ,char*) ; 
 struct usbnet* netdev_priv (int /*<<< orphan*/ ) ; 
 scalar_t__ netif_running (int /*<<< orphan*/ ) ; 
 scalar_t__ qmimux_find_dev (struct usbnet*,int) ; 
 int qmimux_register_device (int /*<<< orphan*/ ,int) ; 
 int restart_syscall () ; 
 int /*<<< orphan*/  rtnl_trylock () ; 
 int /*<<< orphan*/  rtnl_unlock () ; 
 int /*<<< orphan*/  to_net_dev (struct device*) ; 

__attribute__((used)) static ssize_t add_mux_store(struct device *d,  struct device_attribute *attr, const char *buf, size_t len)
{
	struct usbnet *dev = netdev_priv(to_net_dev(d));
	struct qmi_wwan_state *info = (void *)&dev->data;
	u8 mux_id;
	int ret;

	if (kstrtou8(buf, 0, &mux_id))
		return -EINVAL;

	/* mux_id [1 - 254] for compatibility with ip(8) and the rmnet driver */
	if (mux_id < 1 || mux_id > 254)
		return -EINVAL;

	if (!rtnl_trylock())
		return restart_syscall();

	if (qmimux_find_dev(dev, mux_id)) {
		netdev_err(dev->net, "mux_id already present\n");
		ret = -EINVAL;
		goto err;
	}

	/* we don't want to modify a running netdev */
	if (netif_running(dev->net)) {
		netdev_err(dev->net, "Cannot change a running device\n");
		ret = -EBUSY;
		goto err;
	}

	ret = qmimux_register_device(dev->net, mux_id);
	if (!ret) {
		info->flags |= QMI_WWAN_FLAG_MUX;
		ret = len;
	}
err:
	rtnl_unlock();
	return ret;
}