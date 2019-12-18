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
struct se_device {TYPE_1__* transport; } ;
struct config_item {int dummy; } ;
typedef  int /*<<< orphan*/  ssize_t ;
struct TYPE_2__ {int /*<<< orphan*/  (* set_configfs_dev_params ) (struct se_device*,char const*,size_t) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (struct se_device*,char const*,size_t) ; 
 struct se_device* to_device (struct config_item*) ; 

__attribute__((used)) static ssize_t target_dev_control_store(struct config_item *item,
		const char *page, size_t count)
{
	struct se_device *dev = to_device(item);

	return dev->transport->set_configfs_dev_params(dev, page, count);
}