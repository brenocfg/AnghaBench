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
struct spinand_device {int /*<<< orphan*/  oobbuf; } ;
struct nand_pos {int /*<<< orphan*/  target; } ;
struct TYPE_2__ {int /*<<< orphan*/  out; } ;
struct nand_page_io_req {int ooblen; TYPE_1__ oobbuf; int /*<<< orphan*/  ooboffs; struct nand_pos const pos; } ;
struct nand_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 struct spinand_device* nand_to_spinand (struct nand_device*) ; 
 int /*<<< orphan*/  spinand_erase_op (struct spinand_device*,struct nand_pos const*) ; 
 int spinand_select_target (struct spinand_device*,int /*<<< orphan*/ ) ; 
 int spinand_write_enable_op (struct spinand_device*) ; 
 int spinand_write_page (struct spinand_device*,struct nand_page_io_req*) ; 

__attribute__((used)) static int spinand_markbad(struct nand_device *nand, const struct nand_pos *pos)
{
	struct spinand_device *spinand = nand_to_spinand(nand);
	struct nand_page_io_req req = {
		.pos = *pos,
		.ooboffs = 0,
		.ooblen = 2,
		.oobbuf.out = spinand->oobbuf,
	};
	int ret;

	/* Erase block before marking it bad. */
	ret = spinand_select_target(spinand, pos->target);
	if (ret)
		return ret;

	ret = spinand_write_enable_op(spinand);
	if (ret)
		return ret;

	spinand_erase_op(spinand, pos);

	memset(spinand->oobbuf, 0, 2);
	return spinand_write_page(spinand, &req);
}