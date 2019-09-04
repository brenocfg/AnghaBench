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
struct pcd_unit {int /*<<< orphan*/  info; } ;
struct gendisk {struct pcd_unit* private_data; } ;
typedef  int /*<<< orphan*/  fmode_t ;

/* Variables and functions */
 int /*<<< orphan*/  cdrom_release (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pcd_mutex ; 

__attribute__((used)) static void pcd_block_release(struct gendisk *disk, fmode_t mode)
{
	struct pcd_unit *cd = disk->private_data;
	mutex_lock(&pcd_mutex);
	cdrom_release(&cd->info, mode);
	mutex_unlock(&pcd_mutex);
}