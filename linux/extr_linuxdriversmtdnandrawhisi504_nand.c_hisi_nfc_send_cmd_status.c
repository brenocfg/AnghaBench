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
struct hinfc_host {int chipselect; } ;

/* Variables and functions */
 int /*<<< orphan*/  HINFC504_CMD ; 
 int /*<<< orphan*/  HINFC504_DATA_NUM ; 
 int HINFC504_NANDINFO_LEN ; 
 int /*<<< orphan*/  HINFC504_OP ; 
 int HINFC504_OP_CMD1_EN ; 
 int HINFC504_OP_NF_CS_MASK ; 
 int HINFC504_OP_NF_CS_SHIFT ; 
 int HINFC504_OP_READ_DATA_EN ; 
 int NAND_CMD_STATUS ; 
 int /*<<< orphan*/  hinfc_write (struct hinfc_host*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wait_controller_finished (struct hinfc_host*) ; 

__attribute__((used)) static int hisi_nfc_send_cmd_status(struct hinfc_host *host)
{
	hinfc_write(host, HINFC504_NANDINFO_LEN, HINFC504_DATA_NUM);
	hinfc_write(host, NAND_CMD_STATUS, HINFC504_CMD);
	hinfc_write(host, HINFC504_OP_CMD1_EN
		| HINFC504_OP_READ_DATA_EN
		| ((host->chipselect & HINFC504_OP_NF_CS_MASK)
			<< HINFC504_OP_NF_CS_SHIFT),
		HINFC504_OP);

	wait_controller_finished(host);

	return 0;
}