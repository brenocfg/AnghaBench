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
typedef  int u16 ;
struct nand_chip {int dummy; } ;
struct mxc_nand_host {int buf_start; int data_buf; } ;
struct mtd_info {int oobsize; int writesize; } ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int,int) ; 
 int min (int,int) ; 
 struct mxc_nand_host* nand_get_controller_data (struct nand_chip*) ; 
 struct mtd_info* nand_to_mtd (struct nand_chip*) ; 

__attribute__((used)) static void mxc_nand_read_buf(struct nand_chip *nand_chip, u_char *buf,
			      int len)
{
	struct mtd_info *mtd = nand_to_mtd(nand_chip);
	struct mxc_nand_host *host = nand_get_controller_data(nand_chip);
	u16 col = host->buf_start;
	int n = mtd->oobsize + mtd->writesize - col;

	n = min(n, len);

	memcpy(buf, host->data_buf + col, n);

	host->buf_start += n;
}