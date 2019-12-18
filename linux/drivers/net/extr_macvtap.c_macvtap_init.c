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

/* Variables and functions */
 int /*<<< orphan*/  THIS_MODULE ; 
 int class_register (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  class_unregister (int /*<<< orphan*/ *) ; 
 int macvlan_link_register (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  macvtap_cdev ; 
 int /*<<< orphan*/  macvtap_class ; 
 int /*<<< orphan*/  macvtap_link_ops ; 
 int /*<<< orphan*/  macvtap_major ; 
 int /*<<< orphan*/  macvtap_notifier_block ; 
 int register_netdevice_notifier (int /*<<< orphan*/ *) ; 
 int tap_create_cdev (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tap_destroy_cdev (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  unregister_netdevice_notifier (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int macvtap_init(void)
{
	int err;

	err = tap_create_cdev(&macvtap_cdev, &macvtap_major, "macvtap",
			      THIS_MODULE);
	if (err)
		goto out1;

	err = class_register(&macvtap_class);
	if (err)
		goto out2;

	err = register_netdevice_notifier(&macvtap_notifier_block);
	if (err)
		goto out3;

	err = macvlan_link_register(&macvtap_link_ops);
	if (err)
		goto out4;

	return 0;

out4:
	unregister_netdevice_notifier(&macvtap_notifier_block);
out3:
	class_unregister(&macvtap_class);
out2:
	tap_destroy_cdev(macvtap_major, &macvtap_cdev);
out1:
	return err;
}