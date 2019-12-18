#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct mtd_part {TYPE_2__* parent; scalar_t__ offset; } ;
struct mtd_oob_ops {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  corrected; int /*<<< orphan*/  failed; } ;
struct mtd_info {TYPE_1__ ecc_stats; } ;
struct mtd_ecc_stats {scalar_t__ corrected; scalar_t__ failed; } ;
typedef  scalar_t__ loff_t ;
struct TYPE_4__ {int (* _read_oob ) (TYPE_2__*,scalar_t__,struct mtd_oob_ops*) ;struct mtd_ecc_stats ecc_stats; } ;

/* Variables and functions */
 int /*<<< orphan*/  mtd_is_eccerr (int) ; 
 struct mtd_part* mtd_to_part (struct mtd_info*) ; 
 int stub1 (TYPE_2__*,scalar_t__,struct mtd_oob_ops*) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int part_read_oob(struct mtd_info *mtd, loff_t from,
		struct mtd_oob_ops *ops)
{
	struct mtd_part *part = mtd_to_part(mtd);
	struct mtd_ecc_stats stats;
	int res;

	stats = part->parent->ecc_stats;
	res = part->parent->_read_oob(part->parent, from + part->offset, ops);
	if (unlikely(mtd_is_eccerr(res)))
		mtd->ecc_stats.failed +=
			part->parent->ecc_stats.failed - stats.failed;
	else
		mtd->ecc_stats.corrected +=
			part->parent->ecc_stats.corrected - stats.corrected;
	return res;
}