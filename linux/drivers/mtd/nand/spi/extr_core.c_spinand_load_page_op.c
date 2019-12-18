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
struct spinand_device {int /*<<< orphan*/  spimem; } ;
struct spi_mem_op {int dummy; } ;
struct nand_page_io_req {int /*<<< orphan*/  pos; } ;
struct nand_device {int dummy; } ;

/* Variables and functions */
 struct spi_mem_op SPINAND_PAGE_READ_OP (unsigned int) ; 
 unsigned int nanddev_pos_to_row (struct nand_device*,int /*<<< orphan*/ *) ; 
 int spi_mem_exec_op (int /*<<< orphan*/ ,struct spi_mem_op*) ; 
 struct nand_device* spinand_to_nand (struct spinand_device*) ; 

__attribute__((used)) static int spinand_load_page_op(struct spinand_device *spinand,
				const struct nand_page_io_req *req)
{
	struct nand_device *nand = spinand_to_nand(spinand);
	unsigned int row = nanddev_pos_to_row(nand, &req->pos);
	struct spi_mem_op op = SPINAND_PAGE_READ_OP(row);

	return spi_mem_exec_op(spinand->spimem, &op);
}