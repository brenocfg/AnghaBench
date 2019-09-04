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
typedef  int uint8_t ;
struct fsi_master_acf {int /*<<< orphan*/  dev; scalar_t__ sram; } ;

/* Variables and functions */
 scalar_t__ CMD_STAT_REG ; 
 scalar_t__ INT_CNT ; 
 scalar_t__ RSP_DATA ; 
 scalar_t__ STAT_RCRC ; 
 scalar_t__ STAT_RTAG ; 
 scalar_t__ TRACEBUF ; 
 int TR_END ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,char*,...) ; 
 int /*<<< orphan*/  ioread32be (scalar_t__) ; 
 int ioread8 (scalar_t__) ; 
 int /*<<< orphan*/  sprintf (char*,char*,int) ; 

__attribute__((used)) static void dump_ucode_trace(struct fsi_master_acf *master)
{
	char trbuf[52];
	char *p;
	int i;

	dev_dbg(master->dev,
		"CMDSTAT:%08x RTAG=%02x RCRC=%02x RDATA=%02x #INT=%08x\n",
		ioread32be(master->sram + CMD_STAT_REG),
		ioread8(master->sram + STAT_RTAG),
		ioread8(master->sram + STAT_RCRC),
		ioread32be(master->sram + RSP_DATA),
		ioread32be(master->sram + INT_CNT));

	for (i = 0; i < 512; i++) {
		uint8_t v;
		if ((i % 16) == 0)
			p = trbuf;
		v = ioread8(master->sram + TRACEBUF + i);
		p += sprintf(p, "%02x ", v);
		if (((i % 16) == 15) || v == TR_END)
			dev_dbg(master->dev, "%s\n", trbuf);
		if (v == TR_END)
			break;
	}
}