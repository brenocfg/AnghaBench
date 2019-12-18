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
struct nand_chip {int dummy; } ;
struct mxc_nand_host {int status_request; int /*<<< orphan*/  buf_start; int /*<<< orphan*/  main_area0; int /*<<< orphan*/  data_buf; TYPE_1__* devtype_data; int /*<<< orphan*/  dev; } ;
struct mtd_info {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* send_page ) (struct mtd_info*,int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* send_cmd ) (struct mxc_nand_host*,unsigned int,int) ;int /*<<< orphan*/  (* send_read_id ) (struct mxc_nand_host*) ;int /*<<< orphan*/  (* preset ) (struct mtd_info*) ;} ;

/* Variables and functions */
#define  NAND_CMD_ERASE1 133 
#define  NAND_CMD_ERASE2 132 
#define  NAND_CMD_PARAM 131 
#define  NAND_CMD_READID 130 
#define  NAND_CMD_RESET 129 
#define  NAND_CMD_STATUS 128 
 int /*<<< orphan*/  NFC_OUTPUT ; 
 int /*<<< orphan*/  WARN_ONCE (int,char*,unsigned int,...) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,unsigned int,int,int) ; 
 int /*<<< orphan*/  memcpy32_fromio (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mxc_do_addr_cycle (struct mtd_info*,int,int) ; 
 struct mxc_nand_host* nand_get_controller_data (struct nand_chip*) ; 
 struct mtd_info* nand_to_mtd (struct nand_chip*) ; 
 int /*<<< orphan*/  stub1 (struct mtd_info*) ; 
 int /*<<< orphan*/  stub2 (struct mxc_nand_host*,unsigned int,int) ; 
 int /*<<< orphan*/  stub3 (struct mxc_nand_host*,unsigned int,int) ; 
 int /*<<< orphan*/  stub4 (struct mxc_nand_host*,unsigned int,int) ; 
 int /*<<< orphan*/  stub5 (struct mxc_nand_host*) ; 
 int /*<<< orphan*/  stub6 (struct mxc_nand_host*,unsigned int,int) ; 
 int /*<<< orphan*/  stub7 (struct mxc_nand_host*,unsigned int,int) ; 
 int /*<<< orphan*/  stub8 (struct mtd_info*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void mxc_nand_command(struct nand_chip *nand_chip, unsigned command,
			     int column, int page_addr)
{
	struct mtd_info *mtd = nand_to_mtd(nand_chip);
	struct mxc_nand_host *host = nand_get_controller_data(nand_chip);

	dev_dbg(host->dev, "mxc_nand_command (cmd = 0x%x, col = 0x%x, page = 0x%x)\n",
	      command, column, page_addr);

	/* Reset command state information */
	host->status_request = false;

	/* Command pre-processing step */
	switch (command) {
	case NAND_CMD_RESET:
		host->devtype_data->preset(mtd);
		host->devtype_data->send_cmd(host, command, false);
		break;

	case NAND_CMD_STATUS:
		host->buf_start = 0;
		host->status_request = true;

		host->devtype_data->send_cmd(host, command, true);
		WARN_ONCE(column != -1 || page_addr != -1,
			  "Unexpected column/row value (cmd=%u, col=%d, row=%d)\n",
			  command, column, page_addr);
		mxc_do_addr_cycle(mtd, column, page_addr);
		break;

	case NAND_CMD_READID:
		host->devtype_data->send_cmd(host, command, true);
		mxc_do_addr_cycle(mtd, column, page_addr);
		host->devtype_data->send_read_id(host);
		host->buf_start = 0;
		break;

	case NAND_CMD_ERASE1:
	case NAND_CMD_ERASE2:
		host->devtype_data->send_cmd(host, command, false);
		WARN_ONCE(column != -1,
			  "Unexpected column value (cmd=%u, col=%d)\n",
			  command, column);
		mxc_do_addr_cycle(mtd, column, page_addr);

		break;
	case NAND_CMD_PARAM:
		host->devtype_data->send_cmd(host, command, false);
		mxc_do_addr_cycle(mtd, column, page_addr);
		host->devtype_data->send_page(mtd, NFC_OUTPUT);
		memcpy32_fromio(host->data_buf, host->main_area0, 512);
		host->buf_start = 0;
		break;
	default:
		WARN_ONCE(1, "Unimplemented command (cmd=%u)\n",
			  command);
		break;
	}
}