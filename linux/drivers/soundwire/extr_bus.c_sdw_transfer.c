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
struct sdw_msg {int /*<<< orphan*/  dev_num; scalar_t__ page; } ;
struct sdw_bus {int /*<<< orphan*/  msg_lock; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int ENODATA ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int) ; 
 int do_transfer (struct sdw_bus*,struct sdw_msg*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sdw_reset_page (struct sdw_bus*,int /*<<< orphan*/ ) ; 

int sdw_transfer(struct sdw_bus *bus, struct sdw_msg *msg)
{
	int ret;

	mutex_lock(&bus->msg_lock);

	ret = do_transfer(bus, msg);
	if (ret != 0 && ret != -ENODATA)
		dev_err(bus->dev, "trf on Slave %d failed:%d\n",
			msg->dev_num, ret);

	if (msg->page)
		sdw_reset_page(bus, msg->dev_num);

	mutex_unlock(&bus->msg_lock);

	return ret;
}