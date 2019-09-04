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
struct config_item {int dummy; } ;
struct nullb_device {struct config_item item; } ;
struct config_group {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENOMEM ; 
 struct config_item* ERR_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  config_item_init_type_name (struct config_item*,char const*,int /*<<< orphan*/ *) ; 
 struct nullb_device* null_alloc_dev () ; 
 int /*<<< orphan*/  nullb_device_type ; 

__attribute__((used)) static struct
config_item *nullb_group_make_item(struct config_group *group, const char *name)
{
	struct nullb_device *dev;

	dev = null_alloc_dev();
	if (!dev)
		return ERR_PTR(-ENOMEM);

	config_item_init_type_name(&dev->item, name, &nullb_device_type);

	return &dev->item;
}