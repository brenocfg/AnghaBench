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
 int /*<<< orphan*/  debugfs_create_dir (char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  debugfs_create_file (char*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  debugfs_enable_ints_fops ; 
 int /*<<< orphan*/  debugfs_info_fops ; 
 int /*<<< orphan*/  debugfs_remove_recursive (int /*<<< orphan*/ ) ; 
 int visorbus_register_visor_driver (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  visornic_debugfs_dir ; 
 int /*<<< orphan*/  visornic_driver ; 

__attribute__((used)) static int visornic_init(void)
{
	int err;

	visornic_debugfs_dir = debugfs_create_dir("visornic", NULL);

	debugfs_create_file("info", 0400, visornic_debugfs_dir, NULL,
			    &debugfs_info_fops);
	debugfs_create_file("enable_ints", 0200, visornic_debugfs_dir, NULL,
			    &debugfs_enable_ints_fops);

	err = visorbus_register_visor_driver(&visornic_driver);
	if (err)
		debugfs_remove_recursive(visornic_debugfs_dir);

	return err;
}