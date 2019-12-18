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
struct TYPE_2__ {int /*<<< orphan*/  gpmc_nand_data; int /*<<< orphan*/  gpmc_nand_command; } ;
struct omap_nand_info {TYPE_1__ reg; } ;
struct nand_chip {int dummy; } ;

/* Variables and functions */
 int NAND_CMD_STATUS ; 
 int NAND_STATUS_READY ; 
 int /*<<< orphan*/  cond_resched () ; 
 unsigned long jiffies ; 
 scalar_t__ msecs_to_jiffies (int) ; 
 struct omap_nand_info* mtd_to_omap (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nand_to_mtd (struct nand_chip*) ; 
 int readb (int /*<<< orphan*/ ) ; 
 scalar_t__ time_before (unsigned long,unsigned long) ; 
 int /*<<< orphan*/  writeb (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int omap_wait(struct nand_chip *this)
{
	struct omap_nand_info *info = mtd_to_omap(nand_to_mtd(this));
	unsigned long timeo = jiffies;
	int status;

	timeo += msecs_to_jiffies(400);

	writeb(NAND_CMD_STATUS & 0xFF, info->reg.gpmc_nand_command);
	while (time_before(jiffies, timeo)) {
		status = readb(info->reg.gpmc_nand_data);
		if (status & NAND_STATUS_READY)
			break;
		cond_resched();
	}

	status = readb(info->reg.gpmc_nand_data);
	return status;
}