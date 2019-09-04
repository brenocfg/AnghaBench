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
struct hinfc_host {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  HINFC504_CMD ; 
 int /*<<< orphan*/  HINFC504_OP ; 
 int HINFC504_OP_CMD1_EN ; 
 int HINFC504_OP_NF_CS_MASK ; 
 int HINFC504_OP_NF_CS_SHIFT ; 
 int HINFC504_OP_WAIT_READY_EN ; 
 int NAND_CMD_RESET ; 
 int /*<<< orphan*/  hinfc_write (struct hinfc_host*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wait_controller_finished (struct hinfc_host*) ; 

__attribute__((used)) static int hisi_nfc_send_cmd_reset(struct hinfc_host *host, int chipselect)
{
	hinfc_write(host, NAND_CMD_RESET, HINFC504_CMD);

	hinfc_write(host, HINFC504_OP_CMD1_EN
		| ((chipselect & HINFC504_OP_NF_CS_MASK)
			<< HINFC504_OP_NF_CS_SHIFT)
		| HINFC504_OP_WAIT_READY_EN,
		HINFC504_OP);

	wait_controller_finished(host);

	return 0;
}