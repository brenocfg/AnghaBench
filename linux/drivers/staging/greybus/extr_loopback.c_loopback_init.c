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
struct TYPE_2__ {int /*<<< orphan*/  root; int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int class_register (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  class_unregister (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  debugfs_create_dir (char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  debugfs_remove_recursive (int /*<<< orphan*/ ) ; 
 TYPE_1__ gb_dev ; 
 int /*<<< orphan*/  gb_loopback_driver ; 
 int greybus_register (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  loopback_class ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int loopback_init(void)
{
	int retval;

	spin_lock_init(&gb_dev.lock);
	gb_dev.root = debugfs_create_dir("gb_loopback", NULL);

	retval = class_register(&loopback_class);
	if (retval)
		goto err;

	retval = greybus_register(&gb_loopback_driver);
	if (retval)
		goto err_unregister;

	return 0;

err_unregister:
	class_unregister(&loopback_class);
err:
	debugfs_remove_recursive(gb_dev.root);
	return retval;
}