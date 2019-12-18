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
struct hinfc_host {int* addr_value; } ;

/* Variables and functions */
 int /*<<< orphan*/  HINFC504_ADDRH ; 
 int /*<<< orphan*/  HINFC504_ADDRL ; 
 int /*<<< orphan*/  HINFC504_CMD ; 
 int NAND_CMD_PAGEPROG ; 
 int NAND_CMD_SEQIN ; 
 int /*<<< orphan*/  hinfc_write (struct hinfc_host*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hisi_nfc_dma_transfer (struct hinfc_host*,int) ; 

__attribute__((used)) static int hisi_nfc_send_cmd_pageprog(struct hinfc_host *host)
{
	host->addr_value[0] &= 0xffff0000;

	hinfc_write(host, host->addr_value[0], HINFC504_ADDRL);
	hinfc_write(host, host->addr_value[1], HINFC504_ADDRH);
	hinfc_write(host, NAND_CMD_PAGEPROG << 8 | NAND_CMD_SEQIN,
		    HINFC504_CMD);

	hisi_nfc_dma_transfer(host, 1);

	return 0;
}