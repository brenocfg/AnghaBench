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
struct TYPE_2__ {struct config_usb_cfg* label; int /*<<< orphan*/  list; int /*<<< orphan*/  functions; } ;
struct config_usb_cfg {TYPE_1__ c; } ;
struct config_item {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  kfree (struct config_usb_cfg*) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_empty (int /*<<< orphan*/ *) ; 
 struct config_usb_cfg* to_config_usb_cfg (struct config_item*) ; 

__attribute__((used)) static void gadget_config_attr_release(struct config_item *item)
{
	struct config_usb_cfg *cfg = to_config_usb_cfg(item);

	WARN_ON(!list_empty(&cfg->c.functions));
	list_del(&cfg->c.list);
	kfree(cfg->c.label);
	kfree(cfg);
}