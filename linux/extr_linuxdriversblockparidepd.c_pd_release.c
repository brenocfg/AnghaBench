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
struct pd_unit {scalar_t__ removable; int /*<<< orphan*/  access; } ;
struct gendisk {struct pd_unit* private_data; } ;
typedef  int /*<<< orphan*/  fmode_t ;

/* Variables and functions */
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pd_door_unlock ; 
 int /*<<< orphan*/  pd_mutex ; 
 int /*<<< orphan*/  pd_special_command (struct pd_unit*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void pd_release(struct gendisk *p, fmode_t mode)
{
	struct pd_unit *disk = p->private_data;

	mutex_lock(&pd_mutex);
	if (!--disk->access && disk->removable)
		pd_special_command(disk, pd_door_unlock);
	mutex_unlock(&pd_mutex);
}