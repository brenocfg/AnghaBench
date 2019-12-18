#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
union ib_gid {int /*<<< orphan*/ * raw; } ;
typedef  int /*<<< orphan*/  u8 ;
struct usnic_ib_dev {int /*<<< orphan*/  usdev_lock; TYPE_1__* ufdev; } ;
struct ib_device {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  inaddr; int /*<<< orphan*/  mac; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct usnic_ib_dev* to_usdev (struct ib_device*) ; 
 int /*<<< orphan*/  usnic_dbg (char*) ; 
 int /*<<< orphan*/  usnic_mac_ip_to_gid (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

int usnic_ib_query_gid(struct ib_device *ibdev, u8 port, int index,
				union ib_gid *gid)
{

	struct usnic_ib_dev *us_ibdev = to_usdev(ibdev);
	usnic_dbg("\n");

	if (index > 1)
		return -EINVAL;

	mutex_lock(&us_ibdev->usdev_lock);
	memset(&(gid->raw[0]), 0, sizeof(gid->raw));
	usnic_mac_ip_to_gid(us_ibdev->ufdev->mac, us_ibdev->ufdev->inaddr,
			&gid->raw[0]);
	mutex_unlock(&us_ibdev->usdev_lock);

	return 0;
}