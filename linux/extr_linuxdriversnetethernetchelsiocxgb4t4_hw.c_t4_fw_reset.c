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
struct fw_reset_cmd {int /*<<< orphan*/  val; } ;
struct adapter {int dummy; } ;
typedef  int /*<<< orphan*/  c ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_CMD (struct fw_reset_cmd,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RESET ; 
 int /*<<< orphan*/  WRITE ; 
 int /*<<< orphan*/  cpu_to_be32 (int) ; 
 int /*<<< orphan*/  memset (struct fw_reset_cmd*,int /*<<< orphan*/ ,int) ; 
 int t4_wr_mbox (struct adapter*,unsigned int,struct fw_reset_cmd*,int,int /*<<< orphan*/ *) ; 

int t4_fw_reset(struct adapter *adap, unsigned int mbox, int reset)
{
	struct fw_reset_cmd c;

	memset(&c, 0, sizeof(c));
	INIT_CMD(c, RESET, WRITE);
	c.val = cpu_to_be32(reset);
	return t4_wr_mbox(adap, mbox, &c, sizeof(c), NULL);
}