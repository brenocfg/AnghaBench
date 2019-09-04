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
typedef  int /*<<< orphan*/  uint16_t ;
struct nand_chip {int dummy; } ;
struct mxc_nand_host {scalar_t__ buf_start; scalar_t__ data_buf; } ;
struct mtd_info {int dummy; } ;

/* Variables and functions */
 struct nand_chip* mtd_to_nand (struct mtd_info*) ; 
 struct mxc_nand_host* nand_get_controller_data (struct nand_chip*) ; 

__attribute__((used)) static uint16_t mxc_nand_read_word(struct mtd_info *mtd)
{
	struct nand_chip *nand_chip = mtd_to_nand(mtd);
	struct mxc_nand_host *host = nand_get_controller_data(nand_chip);
	uint16_t ret;

	ret = *(uint16_t *)(host->data_buf + host->buf_start);
	host->buf_start += 2;

	return ret;
}