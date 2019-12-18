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
struct irb {int dummy; } ;
struct dasd_device {TYPE_1__* discipline; } ;
struct dasd_ccw_req {struct dasd_device* startdev; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* dump_sense_dbf ) (struct dasd_device*,struct irb*,char*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (struct dasd_device*,struct irb*,char*) ; 

void
dasd_log_sense_dbf(struct dasd_ccw_req *cqr, struct irb *irb)
{
	struct dasd_device *device;

	device = cqr->startdev;
	/* dump sense data to s390 debugfeature*/
	if (device->discipline && device->discipline->dump_sense_dbf)
		device->discipline->dump_sense_dbf(device, irb, "log");
}