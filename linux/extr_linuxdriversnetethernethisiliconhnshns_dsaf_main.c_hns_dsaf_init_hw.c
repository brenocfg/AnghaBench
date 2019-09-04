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
struct TYPE_3__ {int /*<<< orphan*/  name; } ;
struct dsaf_device {TYPE_2__* misc_op; TYPE_1__ ae_dev; int /*<<< orphan*/  dev; } ;
struct TYPE_4__ {int /*<<< orphan*/  (* dsaf_reset ) (struct dsaf_device*,int) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hns_dsaf_comm_init (struct dsaf_device*) ; 
 int /*<<< orphan*/  hns_dsaf_inode_init (struct dsaf_device*) ; 
 int hns_dsaf_sbm_init (struct dsaf_device*) ; 
 int /*<<< orphan*/  hns_dsaf_tbl_init (struct dsaf_device*) ; 
 int /*<<< orphan*/  hns_dsaf_voq_init (struct dsaf_device*) ; 
 int /*<<< orphan*/  mdelay (int) ; 
 int /*<<< orphan*/  stub1 (struct dsaf_device*,int) ; 
 int /*<<< orphan*/  stub2 (struct dsaf_device*,int) ; 

__attribute__((used)) static int hns_dsaf_init_hw(struct dsaf_device *dsaf_dev)
{
	int ret;

	dev_dbg(dsaf_dev->dev,
		"hns_dsaf_init_hw begin %s !\n", dsaf_dev->ae_dev.name);

	dsaf_dev->misc_op->dsaf_reset(dsaf_dev, 0);
	mdelay(10);
	dsaf_dev->misc_op->dsaf_reset(dsaf_dev, 1);

	hns_dsaf_comm_init(dsaf_dev);

	/*init XBAR_INODE*/
	hns_dsaf_inode_init(dsaf_dev);

	/*init SBM*/
	ret = hns_dsaf_sbm_init(dsaf_dev);
	if (ret)
		return ret;

	/*init TBL*/
	hns_dsaf_tbl_init(dsaf_dev);

	/*init VOQ*/
	hns_dsaf_voq_init(dsaf_dev);

	return 0;
}