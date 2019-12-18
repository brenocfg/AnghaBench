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
struct TYPE_2__ {int /*<<< orphan*/  cmd_pdus; } ;
struct se_lun {TYPE_1__ lun_stats; int /*<<< orphan*/  lun_se_dev; } ;
struct se_device {int dummy; } ;
struct config_item {int dummy; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  ENODEV ; 
 int /*<<< orphan*/  PAGE_SIZE ; 
 int /*<<< orphan*/  atomic_long_read (int /*<<< orphan*/ *) ; 
 struct se_device* rcu_dereference (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 
 int /*<<< orphan*/  snprintf (char*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 struct se_lun* to_stat_tgt_port (struct config_item*) ; 

__attribute__((used)) static ssize_t target_stat_tgt_port_in_cmds_show(struct config_item *item,
		char *page)
{
	struct se_lun *lun = to_stat_tgt_port(item);
	struct se_device *dev;
	ssize_t ret = -ENODEV;

	rcu_read_lock();
	dev = rcu_dereference(lun->lun_se_dev);
	if (dev)
		ret = snprintf(page, PAGE_SIZE, "%lu\n",
			       atomic_long_read(&lun->lun_stats.cmd_pdus));
	rcu_read_unlock();
	return ret;
}