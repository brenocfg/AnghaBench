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
typedef  int /*<<< orphan*/  u8 ;
struct spinand_device {int dummy; } ;
struct nand_page_io_req {int dummy; } ;

/* Variables and functions */
 int spinand_check_ecc_status (struct spinand_device*,int /*<<< orphan*/ ) ; 
 int spinand_load_page_op (struct spinand_device*,struct nand_page_io_req const*) ; 
 int spinand_read_from_cache_op (struct spinand_device*,struct nand_page_io_req const*) ; 
 int spinand_wait (struct spinand_device*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int spinand_read_page(struct spinand_device *spinand,
			     const struct nand_page_io_req *req,
			     bool ecc_enabled)
{
	u8 status;
	int ret;

	ret = spinand_load_page_op(spinand, req);
	if (ret)
		return ret;

	ret = spinand_wait(spinand, &status);
	if (ret < 0)
		return ret;

	ret = spinand_read_from_cache_op(spinand, req);
	if (ret)
		return ret;

	if (!ecc_enabled)
		return 0;

	return spinand_check_ecc_status(spinand, status);
}