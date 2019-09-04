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
struct mxc_nand_host {int active_cs; int /*<<< orphan*/  main_area0; int /*<<< orphan*/  data_buf; } ;

/* Variables and functions */
 int NFC_ID ; 
 int /*<<< orphan*/  NFC_V1_V2_BUF_ADDR ; 
 int /*<<< orphan*/  NFC_V1_V2_CONFIG2 ; 
 int /*<<< orphan*/  memcpy32_fromio (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  wait_op_done (struct mxc_nand_host*,int) ; 
 int /*<<< orphan*/  writew (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void send_read_id_v1_v2(struct mxc_nand_host *host)
{
	/* NANDFC buffer 0 is used for device ID output */
	writew(host->active_cs << 4, NFC_V1_V2_BUF_ADDR);

	writew(NFC_ID, NFC_V1_V2_CONFIG2);

	/* Wait for operation to complete */
	wait_op_done(host, true);

	memcpy32_fromio(host->data_buf, host->main_area0, 16);
}