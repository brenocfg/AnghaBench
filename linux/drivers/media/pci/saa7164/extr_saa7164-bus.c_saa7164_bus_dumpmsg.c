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
struct tmComResInfo {int /*<<< orphan*/  seqno; int /*<<< orphan*/  controlselector; int /*<<< orphan*/  command; int /*<<< orphan*/  size; int /*<<< orphan*/  flags; int /*<<< orphan*/  id; } ;
struct saa7164_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DBGLVL_BUS ; 
 int /*<<< orphan*/  dprintk (int /*<<< orphan*/ ,char*,...) ; 

__attribute__((used)) static void saa7164_bus_dumpmsg(struct saa7164_dev *dev, struct tmComResInfo *m,
				void *buf)
{
	dprintk(DBGLVL_BUS, "Dumping msg structure:\n");
	dprintk(DBGLVL_BUS, " .id               = %d\n",   m->id);
	dprintk(DBGLVL_BUS, " .flags            = 0x%x\n", m->flags);
	dprintk(DBGLVL_BUS, " .size             = 0x%x\n", m->size);
	dprintk(DBGLVL_BUS, " .command          = 0x%x\n", m->command);
	dprintk(DBGLVL_BUS, " .controlselector  = 0x%x\n", m->controlselector);
	dprintk(DBGLVL_BUS, " .seqno            = %d\n",   m->seqno);
	if (buf)
		dprintk(DBGLVL_BUS, " .buffer (ignored)\n");
}