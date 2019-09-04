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
typedef  int /*<<< orphan*/  uint8_t ;
struct nand_bbt_descr {int options; } ;
struct mtd_info {int dummy; } ;
typedef  int /*<<< orphan*/  loff_t ;

/* Variables and functions */
 int NAND_BBT_NO_OOB ; 
 int scan_read_data (struct mtd_info*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct nand_bbt_descr*) ; 
 int scan_read_oob (struct mtd_info*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,size_t) ; 

__attribute__((used)) static int scan_read(struct mtd_info *mtd, uint8_t *buf, loff_t offs,
			 size_t len, struct nand_bbt_descr *td)
{
	if (td->options & NAND_BBT_NO_OOB)
		return scan_read_data(mtd, buf, offs, td);
	else
		return scan_read_oob(mtd, buf, offs, len);
}