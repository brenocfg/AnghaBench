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
struct pt_unit {int /*<<< orphan*/  name; struct pi_adapter* pi; } ;
struct pi_adapter {int dummy; } ;

/* Variables and functions */
 int DRIVE (struct pt_unit*) ; 
 int STAT_BUSY ; 
 int STAT_DRQ ; 
 int /*<<< orphan*/  pi_connect (struct pi_adapter*) ; 
 int /*<<< orphan*/  pi_disconnect (struct pi_adapter*) ; 
 int /*<<< orphan*/  pi_write_block (struct pi_adapter*,char*,int) ; 
 int /*<<< orphan*/  printk (char*,int /*<<< orphan*/ ,char*) ; 
 scalar_t__ pt_wait (struct pt_unit*,int,int,char*,char*) ; 
 int read_reg (struct pi_adapter*,int) ; 
 int /*<<< orphan*/  write_reg (struct pi_adapter*,int,int) ; 

__attribute__((used)) static int pt_command(struct pt_unit *tape, char *cmd, int dlen, char *fun)
{
	struct pi_adapter *pi = tape->pi;
	pi_connect(pi);

	write_reg(pi, 6, DRIVE(tape));

	if (pt_wait(tape, STAT_BUSY | STAT_DRQ, 0, fun, "before command")) {
		pi_disconnect(pi);
		return -1;
	}

	write_reg(pi, 4, dlen % 256);
	write_reg(pi, 5, dlen / 256);
	write_reg(pi, 7, 0xa0);	/* ATAPI packet command */

	if (pt_wait(tape, STAT_BUSY, STAT_DRQ, fun, "command DRQ")) {
		pi_disconnect(pi);
		return -1;
	}

	if (read_reg(pi, 2) != 1) {
		printk("%s: %s: command phase error\n", tape->name, fun);
		pi_disconnect(pi);
		return -1;
	}

	pi_write_block(pi, cmd, 12);

	return 0;
}