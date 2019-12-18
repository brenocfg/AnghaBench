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
typedef  int /*<<< orphan*/  u16 ;
struct notifier_block {int dummy; } ;
struct net_device {int dummy; } ;
struct cnic_local {int dummy; } ;
struct cnic_dev {struct cnic_local* cnic_priv; int /*<<< orphan*/  list; } ;

/* Variables and functions */
 unsigned long NETDEV_GOING_DOWN ; 
 unsigned long NETDEV_REGISTER ; 
 unsigned long NETDEV_UNREGISTER ; 
 unsigned long NETDEV_UP ; 
 int NOTIFY_DONE ; 
 int /*<<< orphan*/  VLAN_CFI_MASK ; 
 int /*<<< orphan*/  cnic_dev_lock ; 
 int /*<<< orphan*/  cnic_free_dev (struct cnic_dev*) ; 
 struct cnic_dev* cnic_from_netdev (struct net_device*) ; 
 int /*<<< orphan*/  cnic_get_vlan (struct net_device*,struct net_device**) ; 
 int /*<<< orphan*/  cnic_hold (struct cnic_dev*) ; 
 int /*<<< orphan*/  cnic_put (struct cnic_dev*) ; 
 int /*<<< orphan*/  cnic_rcv_netevent (struct cnic_local*,unsigned long,int /*<<< orphan*/ ) ; 
 scalar_t__ cnic_register_netdev (struct cnic_dev*) ; 
 int /*<<< orphan*/  cnic_start_hw (struct cnic_dev*) ; 
 int /*<<< orphan*/  cnic_stop_hw (struct cnic_dev*) ; 
 int /*<<< orphan*/  cnic_ulp_exit (struct cnic_dev*) ; 
 int /*<<< orphan*/  cnic_ulp_init (struct cnic_dev*) ; 
 int /*<<< orphan*/  cnic_ulp_start (struct cnic_dev*) ; 
 int /*<<< orphan*/  cnic_ulp_stop (struct cnic_dev*) ; 
 int /*<<< orphan*/  cnic_unregister_netdev (struct cnic_dev*) ; 
 struct cnic_dev* is_cnic_dev (struct net_device*) ; 
 int /*<<< orphan*/  list_del_init (int /*<<< orphan*/ *) ; 
 struct net_device* netdev_notifier_info_to_dev (void*) ; 
 int /*<<< orphan*/  write_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  write_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int cnic_netdev_event(struct notifier_block *this, unsigned long event,
							 void *ptr)
{
	struct net_device *netdev = netdev_notifier_info_to_dev(ptr);
	struct cnic_dev *dev;
	int new_dev = 0;

	dev = cnic_from_netdev(netdev);

	if (!dev && event == NETDEV_REGISTER) {
		/* Check for the hot-plug device */
		dev = is_cnic_dev(netdev);
		if (dev) {
			new_dev = 1;
			cnic_hold(dev);
		}
	}
	if (dev) {
		struct cnic_local *cp = dev->cnic_priv;

		if (new_dev)
			cnic_ulp_init(dev);
		else if (event == NETDEV_UNREGISTER)
			cnic_ulp_exit(dev);

		if (event == NETDEV_UP) {
			if (cnic_register_netdev(dev) != 0) {
				cnic_put(dev);
				goto done;
			}
			if (!cnic_start_hw(dev))
				cnic_ulp_start(dev);
		}

		cnic_rcv_netevent(cp, event, 0);

		if (event == NETDEV_GOING_DOWN) {
			cnic_ulp_stop(dev);
			cnic_stop_hw(dev);
			cnic_unregister_netdev(dev);
		} else if (event == NETDEV_UNREGISTER) {
			write_lock(&cnic_dev_lock);
			list_del_init(&dev->list);
			write_unlock(&cnic_dev_lock);

			cnic_put(dev);
			cnic_free_dev(dev);
			goto done;
		}
		cnic_put(dev);
	} else {
		struct net_device *realdev;
		u16 vid;

		vid = cnic_get_vlan(netdev, &realdev);
		if (realdev) {
			dev = cnic_from_netdev(realdev);
			if (dev) {
				vid |= VLAN_CFI_MASK;	/* make non-zero */
				cnic_rcv_netevent(dev->cnic_priv, event, vid);
				cnic_put(dev);
			}
		}
	}
done:
	return NOTIFY_DONE;
}