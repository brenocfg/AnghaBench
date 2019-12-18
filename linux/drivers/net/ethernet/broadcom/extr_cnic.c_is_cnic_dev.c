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
struct net_device {TYPE_1__* ethtool_ops; } ;
struct ethtool_drvinfo {int /*<<< orphan*/  driver; } ;
struct cnic_dev {int /*<<< orphan*/  list; } ;
typedef  int /*<<< orphan*/  drvinfo ;
struct TYPE_2__ {int /*<<< orphan*/  (* get_drvinfo ) (struct net_device*,struct ethtool_drvinfo*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  cnic_dev_list ; 
 int /*<<< orphan*/  cnic_dev_lock ; 
 struct cnic_dev* init_bnx2_cnic (struct net_device*) ; 
 struct cnic_dev* init_bnx2x_cnic (struct net_device*) ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (struct ethtool_drvinfo*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  strcmp (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  stub1 (struct net_device*,struct ethtool_drvinfo*) ; 
 int /*<<< orphan*/  write_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  write_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static struct cnic_dev *is_cnic_dev(struct net_device *dev)
{
	struct ethtool_drvinfo drvinfo;
	struct cnic_dev *cdev = NULL;

	if (dev->ethtool_ops && dev->ethtool_ops->get_drvinfo) {
		memset(&drvinfo, 0, sizeof(drvinfo));
		dev->ethtool_ops->get_drvinfo(dev, &drvinfo);

		if (!strcmp(drvinfo.driver, "bnx2"))
			cdev = init_bnx2_cnic(dev);
		if (!strcmp(drvinfo.driver, "bnx2x"))
			cdev = init_bnx2x_cnic(dev);
		if (cdev) {
			write_lock(&cnic_dev_lock);
			list_add(&cdev->list, &cnic_dev_list);
			write_unlock(&cnic_dev_lock);
		}
	}
	return cdev;
}