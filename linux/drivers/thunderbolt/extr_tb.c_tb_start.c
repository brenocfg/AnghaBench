#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct tb_cm {int hotplug_active; } ;
struct tb {TYPE_1__* root_switch; int /*<<< orphan*/  dev; } ;
struct TYPE_9__ {int no_nvm_upgrade; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (TYPE_1__*) ; 
 int PTR_ERR (TYPE_1__*) ; 
 int /*<<< orphan*/  device_for_each_child (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tb_discover_tunnels (TYPE_1__*) ; 
 struct tb_cm* tb_priv (struct tb*) ; 
 int /*<<< orphan*/  tb_scan_finalize_switch ; 
 int /*<<< orphan*/  tb_scan_switch (TYPE_1__*) ; 
 int tb_switch_add (TYPE_1__*) ; 
 TYPE_1__* tb_switch_alloc (struct tb*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int tb_switch_configure (TYPE_1__*) ; 
 int /*<<< orphan*/  tb_switch_put (TYPE_1__*) ; 

__attribute__((used)) static int tb_start(struct tb *tb)
{
	struct tb_cm *tcm = tb_priv(tb);
	int ret;

	tb->root_switch = tb_switch_alloc(tb, &tb->dev, 0);
	if (IS_ERR(tb->root_switch))
		return PTR_ERR(tb->root_switch);

	/*
	 * ICM firmware upgrade needs running firmware and in native
	 * mode that is not available so disable firmware upgrade of the
	 * root switch.
	 */
	tb->root_switch->no_nvm_upgrade = true;

	ret = tb_switch_configure(tb->root_switch);
	if (ret) {
		tb_switch_put(tb->root_switch);
		return ret;
	}

	/* Announce the switch to the world */
	ret = tb_switch_add(tb->root_switch);
	if (ret) {
		tb_switch_put(tb->root_switch);
		return ret;
	}

	/* Full scan to discover devices added before the driver was loaded. */
	tb_scan_switch(tb->root_switch);
	/* Find out tunnels created by the boot firmware */
	tb_discover_tunnels(tb->root_switch);
	/* Make the discovered switches available to the userspace */
	device_for_each_child(&tb->root_switch->dev, NULL,
			      tb_scan_finalize_switch);

	/* Allow tb_handle_hotplug to progress events */
	tcm->hotplug_active = true;
	return 0;
}