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
struct usb_os_desc_ext_prop {scalar_t__ data_len; scalar_t__ name_len; int /*<<< orphan*/  name; int /*<<< orphan*/  entry; } ;
struct usb_os_desc {scalar_t__ opts_mutex; int /*<<< orphan*/  ext_prop_len; int /*<<< orphan*/  ext_prop_count; } ;
struct config_item {int dummy; } ;
struct config_group {int /*<<< orphan*/  cg_item; } ;

/* Variables and functions */
 int /*<<< orphan*/  config_item_put (struct config_item*) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (scalar_t__) ; 
 int /*<<< orphan*/  mutex_unlock (scalar_t__) ; 
 struct usb_os_desc* to_usb_os_desc (int /*<<< orphan*/ *) ; 
 struct usb_os_desc_ext_prop* to_usb_os_desc_ext_prop (struct config_item*) ; 

__attribute__((used)) static void ext_prop_drop(struct config_group *group, struct config_item *item)
{
	struct usb_os_desc_ext_prop *ext_prop = to_usb_os_desc_ext_prop(item);
	struct usb_os_desc *desc = to_usb_os_desc(&group->cg_item);

	if (desc->opts_mutex)
		mutex_lock(desc->opts_mutex);
	list_del(&ext_prop->entry);
	--desc->ext_prop_count;
	kfree(ext_prop->name);
	desc->ext_prop_len -= (ext_prop->name_len + ext_prop->data_len + 14);
	if (desc->opts_mutex)
		mutex_unlock(desc->opts_mutex);
	config_item_put(item);
}