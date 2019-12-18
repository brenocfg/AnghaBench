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
struct dasd_device {int dummy; } ;
struct dasd_ccw_req {scalar_t__ function; char* retries; int /*<<< orphan*/  status; struct dasd_device* startdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DASD_CQR_FILLED ; 
 int /*<<< orphan*/  DBF_DEV_EVENT (int /*<<< orphan*/ ,struct dasd_device*,char*,char*) ; 
 int /*<<< orphan*/  DBF_INFO ; 
 int HZ ; 
 int /*<<< orphan*/  dasd_3990_erp_block_queue (struct dasd_ccw_req*,int) ; 

__attribute__((used)) static struct dasd_ccw_req *
dasd_3990_erp_action_4(struct dasd_ccw_req * erp, char *sense)
{

	struct dasd_device *device = erp->startdev;

	/* first time set initial retry counter and erp_function    */
	/* and retry once without waiting for state change pending  */
	/* interrupt (this enables easier enqueing of the cqr)	    */
	if (erp->function != dasd_3990_erp_action_4) {

		DBF_DEV_EVENT(DBF_INFO, device, "%s",
			    "dasd_3990_erp_action_4: first time retry");

		erp->retries = 256;
		erp->function = dasd_3990_erp_action_4;

	} else {
		if (sense && (sense[25] == 0x1D)) { /* state change pending */

			DBF_DEV_EVENT(DBF_INFO, device,
				    "waiting for state change pending "
				    "interrupt, %d retries left",
				    erp->retries);

			dasd_3990_erp_block_queue(erp, 30*HZ);

		} else if (sense && (sense[25] == 0x1E)) {	/* busy */
			DBF_DEV_EVENT(DBF_INFO, device,
				    "busy - redriving request later, "
				    "%d retries left",
				    erp->retries);
                        dasd_3990_erp_block_queue(erp, HZ);
		} else {
			/* no state change pending - retry */
			DBF_DEV_EVENT(DBF_INFO, device,
				     "redriving request immediately, "
				     "%d retries left",
				     erp->retries);
			erp->status = DASD_CQR_FILLED;
		}
	}

	return erp;

}