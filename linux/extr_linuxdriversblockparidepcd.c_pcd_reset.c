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
struct pcd_unit {int drive; int /*<<< orphan*/  pi; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int HZ ; 
 int IDE_BUSY ; 
 int /*<<< orphan*/  PCD_RESET_TMO ; 
 int /*<<< orphan*/  pcd_sleep (int) ; 
 int /*<<< orphan*/  pi_connect (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pi_disconnect (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printk (char*,...) ; 
 int read_reg (struct pcd_unit*,int) ; 
 int status_reg (struct pcd_unit*) ; 
 scalar_t__ verbose ; 
 int /*<<< orphan*/  write_reg (struct pcd_unit*,int,int) ; 

__attribute__((used)) static int pcd_reset(struct pcd_unit *cd)
{
	int i, k, flg;
	int expect[5] = { 1, 1, 1, 0x14, 0xeb };

	pi_connect(cd->pi);
	write_reg(cd, 6, 0xa0 + 0x10 * cd->drive);
	write_reg(cd, 7, 8);

	pcd_sleep(20 * HZ / 1000);	/* delay a bit */

	k = 0;
	while ((k++ < PCD_RESET_TMO) && (status_reg(cd) & IDE_BUSY))
		pcd_sleep(HZ / 10);

	flg = 1;
	for (i = 0; i < 5; i++)
		flg &= (read_reg(cd, i + 1) == expect[i]);

	if (verbose) {
		printk("%s: Reset (%d) signature = ", cd->name, k);
		for (i = 0; i < 5; i++)
			printk("%3x", read_reg(cd, i + 1));
		if (!flg)
			printk(" (incorrect)");
		printk("\n");
	}

	pi_disconnect(cd->pi);
	return flg - 1;
}