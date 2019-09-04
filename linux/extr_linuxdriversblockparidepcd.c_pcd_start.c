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

/* Variables and functions */
 int /*<<< orphan*/  BLK_STS_IOERR ; 
 int /*<<< orphan*/  PCD_TMO ; 
 int /*<<< orphan*/  do_pcd_read_drq ; 
 int /*<<< orphan*/  mdelay (int) ; 
 int /*<<< orphan*/  next_request (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nice ; 
 int pcd_bufblk ; 
 scalar_t__ pcd_command (int /*<<< orphan*/ ,char*,int,char*) ; 
 int /*<<< orphan*/  pcd_current ; 
 int /*<<< orphan*/  pcd_ready ; 
 int pcd_sector ; 
 int /*<<< orphan*/  ps_set_intr (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void pcd_start(void)
{
	int b, i;
	char rd_cmd[12] = { 0xa8, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0 };

	pcd_bufblk = pcd_sector / 4;
	b = pcd_bufblk;
	for (i = 0; i < 4; i++) {
		rd_cmd[5 - i] = b & 0xff;
		b = b >> 8;
	}

	if (pcd_command(pcd_current, rd_cmd, 2048, "read block")) {
		pcd_bufblk = -1;
		next_request(BLK_STS_IOERR);
		return;
	}

	mdelay(1);

	ps_set_intr(do_pcd_read_drq, pcd_ready, PCD_TMO, nice);
}