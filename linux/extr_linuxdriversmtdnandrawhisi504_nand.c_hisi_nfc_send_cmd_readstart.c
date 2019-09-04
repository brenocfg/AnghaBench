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
struct mtd_info {int writesize; int oobsize; } ;
struct hinfc_host {int* addr_value; int* cache_addr_value; int /*<<< orphan*/  chip; } ;

/* Variables and functions */
 int /*<<< orphan*/  HINFC504_ADDRH ; 
 int /*<<< orphan*/  HINFC504_ADDRL ; 
 int /*<<< orphan*/  HINFC504_CMD ; 
 int /*<<< orphan*/  HINFC504_LOG_READ_ADDR ; 
 int /*<<< orphan*/  HINFC504_LOG_READ_LEN ; 
 int NAND_CMD_READ0 ; 
 int NAND_CMD_READSTART ; 
 int /*<<< orphan*/  hinfc_write (struct hinfc_host*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hisi_nfc_dma_transfer (struct hinfc_host*,int /*<<< orphan*/ ) ; 
 struct mtd_info* nand_to_mtd (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int hisi_nfc_send_cmd_readstart(struct hinfc_host *host)
{
	struct mtd_info	*mtd = nand_to_mtd(&host->chip);

	if ((host->addr_value[0] == host->cache_addr_value[0]) &&
	    (host->addr_value[1] == host->cache_addr_value[1]))
		return 0;

	host->addr_value[0] &= 0xffff0000;

	hinfc_write(host, host->addr_value[0], HINFC504_ADDRL);
	hinfc_write(host, host->addr_value[1], HINFC504_ADDRH);
	hinfc_write(host, NAND_CMD_READSTART << 8 | NAND_CMD_READ0,
		    HINFC504_CMD);

	hinfc_write(host, 0, HINFC504_LOG_READ_ADDR);
	hinfc_write(host, mtd->writesize + mtd->oobsize,
		    HINFC504_LOG_READ_LEN);

	hisi_nfc_dma_transfer(host, 0);

	host->cache_addr_value[0] = host->addr_value[0];
	host->cache_addr_value[1] = host->addr_value[1];

	return 0;
}