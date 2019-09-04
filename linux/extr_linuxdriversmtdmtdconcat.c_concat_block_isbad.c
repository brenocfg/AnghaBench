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
struct mtd_info {scalar_t__ size; } ;
struct mtd_concat {int num_subdev; struct mtd_info** subdev; } ;
typedef  scalar_t__ loff_t ;

/* Variables and functions */
 struct mtd_concat* CONCAT (struct mtd_info*) ; 
 int mtd_block_isbad (struct mtd_info*,scalar_t__) ; 
 int /*<<< orphan*/  mtd_can_have_bb (struct mtd_info*) ; 

__attribute__((used)) static int concat_block_isbad(struct mtd_info *mtd, loff_t ofs)
{
	struct mtd_concat *concat = CONCAT(mtd);
	int i, res = 0;

	if (!mtd_can_have_bb(concat->subdev[0]))
		return res;

	for (i = 0; i < concat->num_subdev; i++) {
		struct mtd_info *subdev = concat->subdev[i];

		if (ofs >= subdev->size) {
			ofs -= subdev->size;
			continue;
		}

		res = mtd_block_isbad(subdev, ofs);
		break;
	}

	return res;
}