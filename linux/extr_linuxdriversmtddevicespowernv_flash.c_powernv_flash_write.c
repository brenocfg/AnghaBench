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
typedef  int /*<<< orphan*/  u_char ;
struct mtd_info {int dummy; } ;
typedef  int /*<<< orphan*/  loff_t ;

/* Variables and functions */
 int /*<<< orphan*/  FLASH_OP_WRITE ; 
 int powernv_flash_async_op (struct mtd_info*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,size_t,size_t*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int powernv_flash_write(struct mtd_info *mtd, loff_t to, size_t len,
		     size_t *retlen, const u_char *buf)
{
	return powernv_flash_async_op(mtd, FLASH_OP_WRITE, to,
			len, retlen, (u_char *)buf);
}