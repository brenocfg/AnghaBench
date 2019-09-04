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
struct uio_info {struct cnic_uio_dev* priv; } ;
struct inode {int dummy; } ;
struct cnic_uio_dev {int uio_dev; struct cnic_dev* dev; } ;
struct cnic_dev {int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  CAP_NET_ADMIN ; 
 int /*<<< orphan*/  CNIC_F_CNIC_UP ; 
 int EBUSY ; 
 int ENODEV ; 
 int EPERM ; 
 int /*<<< orphan*/  capable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cnic_init_rings (struct cnic_dev*) ; 
 int /*<<< orphan*/  cnic_shutdown_rings (struct cnic_dev*) ; 
 int iminor (struct inode*) ; 
 int /*<<< orphan*/  rtnl_lock () ; 
 int /*<<< orphan*/  rtnl_unlock () ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int cnic_uio_open(struct uio_info *uinfo, struct inode *inode)
{
	struct cnic_uio_dev *udev = uinfo->priv;
	struct cnic_dev *dev;

	if (!capable(CAP_NET_ADMIN))
		return -EPERM;

	if (udev->uio_dev != -1)
		return -EBUSY;

	rtnl_lock();
	dev = udev->dev;

	if (!dev || !test_bit(CNIC_F_CNIC_UP, &dev->flags)) {
		rtnl_unlock();
		return -ENODEV;
	}

	udev->uio_dev = iminor(inode);

	cnic_shutdown_rings(dev);
	cnic_init_rings(dev);
	rtnl_unlock();

	return 0;
}