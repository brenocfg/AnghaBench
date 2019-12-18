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
struct ubi_volume_desc {struct ubi_volume* vol; } ;
struct ubi_volume {int /*<<< orphan*/  used_bytes; int /*<<< orphan*/  ubi; scalar_t__ updating; } ;
struct file {struct ubi_volume_desc* private_data; } ;
typedef  int /*<<< orphan*/  loff_t ;

/* Variables and functions */
 int /*<<< orphan*/  EBUSY ; 
 int /*<<< orphan*/  fixed_size_llseek (struct file*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ubi_err (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static loff_t vol_cdev_llseek(struct file *file, loff_t offset, int origin)
{
	struct ubi_volume_desc *desc = file->private_data;
	struct ubi_volume *vol = desc->vol;

	if (vol->updating) {
		/* Update is in progress, seeking is prohibited */
		ubi_err(vol->ubi, "updating");
		return -EBUSY;
	}

	return fixed_size_llseek(file, offset, origin, vol->used_bytes);
}