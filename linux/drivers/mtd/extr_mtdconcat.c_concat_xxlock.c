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
typedef  scalar_t__ uint64_t ;
struct mtd_info {scalar_t__ size; } ;
struct mtd_concat {int num_subdev; struct mtd_info** subdev; } ;
typedef  scalar_t__ loff_t ;

/* Variables and functions */
 struct mtd_concat* CONCAT (struct mtd_info*) ; 
 int EINVAL ; 
 int mtd_lock (struct mtd_info*,scalar_t__,scalar_t__) ; 
 int mtd_unlock (struct mtd_info*,scalar_t__,scalar_t__) ; 

__attribute__((used)) static int concat_xxlock(struct mtd_info *mtd, loff_t ofs, uint64_t len,
			 bool is_lock)
{
	struct mtd_concat *concat = CONCAT(mtd);
	int i, err = -EINVAL;

	for (i = 0; i < concat->num_subdev; i++) {
		struct mtd_info *subdev = concat->subdev[i];
		uint64_t size;

		if (ofs >= subdev->size) {
			size = 0;
			ofs -= subdev->size;
			continue;
		}
		if (ofs + len > subdev->size)
			size = subdev->size - ofs;
		else
			size = len;

		if (is_lock)
			err = mtd_lock(subdev, ofs, size);
		else
			err = mtd_unlock(subdev, ofs, size);
		if (err)
			break;

		len -= size;
		if (len == 0)
			break;

		err = -EINVAL;
		ofs = 0;
	}

	return err;
}