#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int dt; int period; int check_nego; } ;
struct sym_tcb {TYPE_1__ tgoal; } ;
struct sym_hcb {int minsync; struct sym_tcb* target; } ;
struct TYPE_4__ {int /*<<< orphan*/  parent; } ;
struct scsi_target {size_t id; TYPE_2__ dev; } ;
struct Scsi_Host {int dummy; } ;

/* Variables and functions */
 struct Scsi_Host* dev_to_shost (int /*<<< orphan*/ ) ; 
 scalar_t__ spi_width (struct scsi_target*) ; 
 struct sym_hcb* sym_get_hcb (struct Scsi_Host*) ; 

__attribute__((used)) static void sym2_set_period(struct scsi_target *starget, int period)
{
	struct Scsi_Host *shost = dev_to_shost(starget->dev.parent);
	struct sym_hcb *np = sym_get_hcb(shost);
	struct sym_tcb *tp = &np->target[starget->id];

	/* have to have DT for these transfers, but DT will also
	 * set width, so check that this is allowed */
	if (period <= np->minsync && spi_width(starget))
		tp->tgoal.dt = 1;

	tp->tgoal.period = period;
	tp->tgoal.check_nego = 1;
}