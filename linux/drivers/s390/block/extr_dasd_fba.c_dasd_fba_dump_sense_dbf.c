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
typedef  int /*<<< orphan*/  u64 ;
struct irb {int /*<<< orphan*/  scsw; } ;
struct dasd_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DBF_DEV_EVENT (int /*<<< orphan*/ ,struct dasd_device*,char*,char*,...) ; 
 int /*<<< orphan*/  DBF_EMERG ; 
 scalar_t__ dasd_get_sense (struct irb*) ; 
 int /*<<< orphan*/  scsw_cc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  scsw_cstat (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  scsw_dstat (int /*<<< orphan*/ *) ; 
 scalar_t__ scsw_is_tm (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
dasd_fba_dump_sense_dbf(struct dasd_device *device, struct irb *irb,
			char *reason)
{
	u64 *sense;

	sense = (u64 *) dasd_get_sense(irb);
	if (sense) {
		DBF_DEV_EVENT(DBF_EMERG, device,
			      "%s: %s %02x%02x%02x %016llx %016llx %016llx "
			      "%016llx", reason,
			      scsw_is_tm(&irb->scsw) ? "t" : "c",
			      scsw_cc(&irb->scsw), scsw_cstat(&irb->scsw),
			      scsw_dstat(&irb->scsw), sense[0], sense[1],
			      sense[2], sense[3]);
	} else {
		DBF_DEV_EVENT(DBF_EMERG, device, "%s",
			      "SORRY - NO VALID SENSE AVAILABLE\n");
	}
}