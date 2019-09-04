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
struct ide_tape_obj {int dummy; } ;
struct gendisk {int dummy; } ;
typedef  int /*<<< orphan*/  fmode_t ;

/* Variables and functions */
 struct ide_tape_obj* ide_drv_g (struct gendisk*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ide_tape_mutex ; 
 int /*<<< orphan*/  ide_tape_obj ; 
 int /*<<< orphan*/  ide_tape_put (struct ide_tape_obj*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void idetape_release(struct gendisk *disk, fmode_t mode)
{
	struct ide_tape_obj *tape = ide_drv_g(disk, ide_tape_obj);

	mutex_lock(&ide_tape_mutex);
	ide_tape_put(tape);
	mutex_unlock(&ide_tape_mutex);
}