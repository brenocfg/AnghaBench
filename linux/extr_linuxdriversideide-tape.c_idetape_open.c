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
struct block_device {int /*<<< orphan*/  bd_disk; } ;
typedef  int /*<<< orphan*/  fmode_t ;

/* Variables and functions */
 int ENXIO ; 
 struct ide_tape_obj* ide_tape_get (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ide_tape_mutex ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int idetape_open(struct block_device *bdev, fmode_t mode)
{
	struct ide_tape_obj *tape;

	mutex_lock(&ide_tape_mutex);
	tape = ide_tape_get(bdev->bd_disk, false, 0);
	mutex_unlock(&ide_tape_mutex);

	if (!tape)
		return -ENXIO;

	return 0;
}