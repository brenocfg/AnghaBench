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
typedef  unsigned int u16 ;
struct spinand_device {int dummy; } ;
struct TYPE_4__ {unsigned int plane; } ;
struct nand_page_io_req {TYPE_2__ pos; } ;
struct TYPE_3__ {int planes_per_lun; int /*<<< orphan*/  pagesize; } ;
struct nand_device {TYPE_1__ memorg; } ;

/* Variables and functions */
 unsigned int fls (int /*<<< orphan*/ ) ; 
 struct nand_device* spinand_to_nand (struct spinand_device*) ; 

__attribute__((used)) static void spinand_cache_op_adjust_colum(struct spinand_device *spinand,
					  const struct nand_page_io_req *req,
					  u16 *column)
{
	struct nand_device *nand = spinand_to_nand(spinand);
	unsigned int shift;

	if (nand->memorg.planes_per_lun < 2)
		return;

	/* The plane number is passed in MSB just above the column address */
	shift = fls(nand->memorg.pagesize);
	*column |= req->pos.plane << shift;
}