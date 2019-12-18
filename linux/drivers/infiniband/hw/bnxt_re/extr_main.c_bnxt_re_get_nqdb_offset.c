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
typedef  int u32 ;
typedef  size_t u16 ;
struct bnxt_re_dev {TYPE_1__* msix_entries; int /*<<< orphan*/  chip_ctx; } ;
struct TYPE_2__ {int db_offset; } ;

/* Variables and functions */
 scalar_t__ bnxt_qplib_is_chip_gen_p5 (int /*<<< orphan*/ *) ; 

__attribute__((used)) static u32 bnxt_re_get_nqdb_offset(struct bnxt_re_dev *rdev, u16 indx)
{
	return bnxt_qplib_is_chip_gen_p5(&rdev->chip_ctx) ?
				0x10000 : rdev->msix_entries[indx].db_offset;
}