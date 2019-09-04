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
typedef  int u8 ;
struct nand_chip {scalar_t__ (* dev_ready ) (struct mtd_info*) ;} ;
struct mtd_info {int dummy; } ;
typedef  int /*<<< orphan*/  status ;

/* Variables and functions */
 int NAND_STATUS_READY ; 
 int /*<<< orphan*/  mdelay (int) ; 
 int nand_read_data_op (struct nand_chip*,int*,int,int) ; 
 scalar_t__ stub1 (struct mtd_info*) ; 

__attribute__((used)) static void panic_nand_wait(struct mtd_info *mtd, struct nand_chip *chip,
			    unsigned long timeo)
{
	int i;
	for (i = 0; i < timeo; i++) {
		if (chip->dev_ready) {
			if (chip->dev_ready(mtd))
				break;
		} else {
			int ret;
			u8 status;

			ret = nand_read_data_op(chip, &status, sizeof(status),
						true);
			if (ret)
				return;

			if (status & NAND_STATUS_READY)
				break;
		}
		mdelay(1);
	}
}