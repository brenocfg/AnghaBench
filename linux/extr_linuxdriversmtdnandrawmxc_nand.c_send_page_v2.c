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
struct nand_chip {int dummy; } ;
struct mxc_nand_host {int active_cs; } ;
struct mtd_info {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  NFC_V1_V2_BUF_ADDR ; 
 int /*<<< orphan*/  NFC_V1_V2_CONFIG2 ; 
 struct nand_chip* mtd_to_nand (struct mtd_info*) ; 
 struct mxc_nand_host* nand_get_controller_data (struct nand_chip*) ; 
 int /*<<< orphan*/  wait_op_done (struct mxc_nand_host*,int) ; 
 int /*<<< orphan*/  writew (unsigned int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void send_page_v2(struct mtd_info *mtd, unsigned int ops)
{
	struct nand_chip *nand_chip = mtd_to_nand(mtd);
	struct mxc_nand_host *host = nand_get_controller_data(nand_chip);

	/* NANDFC buffer 0 is used for page read/write */
	writew(host->active_cs << 4, NFC_V1_V2_BUF_ADDR);

	writew(ops, NFC_V1_V2_CONFIG2);

	/* Wait for operation to complete */
	wait_op_done(host, true);
}