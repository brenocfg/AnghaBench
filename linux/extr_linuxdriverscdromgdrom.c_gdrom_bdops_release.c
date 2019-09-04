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
struct gendisk {int dummy; } ;
typedef  int /*<<< orphan*/  fmode_t ;
struct TYPE_2__ {int /*<<< orphan*/  cd_info; } ;

/* Variables and functions */
 int /*<<< orphan*/  cdrom_release (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_1__ gd ; 
 int /*<<< orphan*/  gdrom_mutex ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void gdrom_bdops_release(struct gendisk *disk, fmode_t mode)
{
	mutex_lock(&gdrom_mutex);
	cdrom_release(gd.cd_info, mode);
	mutex_unlock(&gdrom_mutex);
}