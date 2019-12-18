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
struct ide_tape_obj {int /*<<< orphan*/  dev; int /*<<< orphan*/  drive; } ;
struct gendisk {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  get_device (int /*<<< orphan*/ *) ; 
 scalar_t__ ide_device_get (int /*<<< orphan*/ ) ; 
 struct ide_tape_obj* ide_drv_g (struct gendisk*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ide_tape_obj ; 
 struct ide_tape_obj** idetape_devs ; 
 int /*<<< orphan*/  idetape_ref_mutex ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static struct ide_tape_obj *ide_tape_get(struct gendisk *disk, bool cdev,
					 unsigned int i)
{
	struct ide_tape_obj *tape = NULL;

	mutex_lock(&idetape_ref_mutex);

	if (cdev)
		tape = idetape_devs[i];
	else
		tape = ide_drv_g(disk, ide_tape_obj);

	if (tape) {
		if (ide_device_get(tape->drive))
			tape = NULL;
		else
			get_device(&tape->dev);
	}

	mutex_unlock(&idetape_ref_mutex);
	return tape;
}