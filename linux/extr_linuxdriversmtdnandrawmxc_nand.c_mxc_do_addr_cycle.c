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
struct nand_chip {int options; } ;
struct mxc_nand_host {TYPE_1__* devtype_data; } ;
struct mtd_info {int writesize; int size; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* send_addr ) (struct mxc_nand_host*,int,int) ;} ;

/* Variables and functions */
 int NAND_ROW_ADDR_3 ; 
 struct nand_chip* mtd_to_nand (struct mtd_info*) ; 
 struct mxc_nand_host* nand_get_controller_data (struct nand_chip*) ; 
 int /*<<< orphan*/  stub1 (struct mxc_nand_host*,int,int) ; 
 int /*<<< orphan*/  stub2 (struct mxc_nand_host*,int,int) ; 
 int /*<<< orphan*/  stub3 (struct mxc_nand_host*,int,int) ; 
 int /*<<< orphan*/  stub4 (struct mxc_nand_host*,int,int) ; 
 int /*<<< orphan*/  stub5 (struct mxc_nand_host*,int,int) ; 
 int /*<<< orphan*/  stub6 (struct mxc_nand_host*,int,int) ; 
 int /*<<< orphan*/  stub7 (struct mxc_nand_host*,int,int) ; 
 int /*<<< orphan*/  stub8 (struct mxc_nand_host*,int,int) ; 
 int /*<<< orphan*/  stub9 (struct mxc_nand_host*,int,int) ; 

__attribute__((used)) static void mxc_do_addr_cycle(struct mtd_info *mtd, int column, int page_addr)
{
	struct nand_chip *nand_chip = mtd_to_nand(mtd);
	struct mxc_nand_host *host = nand_get_controller_data(nand_chip);

	/* Write out column address, if necessary */
	if (column != -1) {
		host->devtype_data->send_addr(host, column & 0xff,
					      page_addr == -1);
		if (mtd->writesize > 512)
			/* another col addr cycle for 2k page */
			host->devtype_data->send_addr(host,
						      (column >> 8) & 0xff,
						      false);
	}

	/* Write out page address, if necessary */
	if (page_addr != -1) {
		/* paddr_0 - p_addr_7 */
		host->devtype_data->send_addr(host, (page_addr & 0xff), false);

		if (mtd->writesize > 512) {
			if (mtd->size >= 0x10000000) {
				/* paddr_8 - paddr_15 */
				host->devtype_data->send_addr(host,
						(page_addr >> 8) & 0xff,
						false);
				host->devtype_data->send_addr(host,
						(page_addr >> 16) & 0xff,
						true);
			} else
				/* paddr_8 - paddr_15 */
				host->devtype_data->send_addr(host,
						(page_addr >> 8) & 0xff, true);
		} else {
			if (nand_chip->options & NAND_ROW_ADDR_3) {
				/* paddr_8 - paddr_15 */
				host->devtype_data->send_addr(host,
						(page_addr >> 8) & 0xff,
						false);
				host->devtype_data->send_addr(host,
						(page_addr >> 16) & 0xff,
						true);
			} else
				/* paddr_8 - paddr_15 */
				host->devtype_data->send_addr(host,
						(page_addr >> 8) & 0xff, true);
		}
	}
}