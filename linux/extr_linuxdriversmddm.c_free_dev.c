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
struct mapped_device {int /*<<< orphan*/  stats; int /*<<< orphan*/  table_devices; int /*<<< orphan*/  disk; } ;

/* Variables and functions */
 int MINOR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  THIS_MODULE ; 
 int /*<<< orphan*/  cleanup_mapped_device (struct mapped_device*) ; 
 int /*<<< orphan*/  disk_devt (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dm_stats_cleanup (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free_minor (int) ; 
 int /*<<< orphan*/  free_table_devices (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kvfree (struct mapped_device*) ; 
 int /*<<< orphan*/  module_put (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  unlock_fs (struct mapped_device*) ; 

__attribute__((used)) static void free_dev(struct mapped_device *md)
{
	int minor = MINOR(disk_devt(md->disk));

	unlock_fs(md);

	cleanup_mapped_device(md);

	free_table_devices(&md->table_devices);
	dm_stats_cleanup(&md->stats);
	free_minor(minor);

	module_put(THIS_MODULE);
	kvfree(md);
}