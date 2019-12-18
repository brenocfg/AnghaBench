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
struct mtd_info {int dummy; } ;
struct erase_info {int /*<<< orphan*/  addr; int /*<<< orphan*/  fail_addr; int /*<<< orphan*/  len; } ;

/* Variables and functions */
 int /*<<< orphan*/  FLASH_OP_ERASE ; 
 int powernv_flash_async_op (struct mtd_info*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int powernv_flash_erase(struct mtd_info *mtd, struct erase_info *erase)
{
	int rc;

	rc =  powernv_flash_async_op(mtd, FLASH_OP_ERASE, erase->addr,
			erase->len, NULL, NULL);
	if (rc)
		erase->fail_addr = erase->addr;

	return rc;
}