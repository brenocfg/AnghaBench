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
typedef  int /*<<< orphan*/  uint8_t ;
struct fsi_slave {int link; int /*<<< orphan*/  dev; int /*<<< orphan*/  id; struct fsi_master* master; } ;
struct fsi_master {int dummy; } ;
typedef  int /*<<< orphan*/  stat ;
typedef  int /*<<< orphan*/  irq ;
typedef  int /*<<< orphan*/  __be32 ;

/* Variables and functions */
 scalar_t__ FSI_SISC ; 
 scalar_t__ FSI_SLAVE_BASE ; 
 scalar_t__ FSI_SSTAT ; 
 int /*<<< orphan*/  be32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int fsi_master_read (struct fsi_master*,int,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ *,int) ; 
 int fsi_master_write (struct fsi_master*,int,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int fsi_slave_report_and_clear_errors(struct fsi_slave *slave)
{
	struct fsi_master *master = slave->master;
	__be32 irq, stat;
	int rc, link;
	uint8_t id;

	link = slave->link;
	id = slave->id;

	rc = fsi_master_read(master, link, id, FSI_SLAVE_BASE + FSI_SISC,
			&irq, sizeof(irq));
	if (rc)
		return rc;

	rc =  fsi_master_read(master, link, id, FSI_SLAVE_BASE + FSI_SSTAT,
			&stat, sizeof(stat));
	if (rc)
		return rc;

	dev_dbg(&slave->dev, "status: 0x%08x, sisc: 0x%08x\n",
			be32_to_cpu(stat), be32_to_cpu(irq));

	/* clear interrupts */
	return fsi_master_write(master, link, id, FSI_SLAVE_BASE + FSI_SISC,
			&irq, sizeof(irq));
}