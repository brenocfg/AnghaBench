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
struct dasd_ccw_req {struct dasd_ccw_req* (* function ) (struct dasd_ccw_req*,char*) ;struct dasd_device* startdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DBF_DEV_EVENT (int /*<<< orphan*/ ,struct dasd_device*,char*,char*) ; 
 int /*<<< orphan*/  DBF_WARNING ; 
 struct dasd_ccw_req* dasd_3990_erp_action_5 (struct dasd_ccw_req*) ; 

__attribute__((used)) static struct dasd_ccw_req *
dasd_3990_erp_overrun(struct dasd_ccw_req * erp, char *sense)
{

	struct dasd_device *device = erp->startdev;

	erp->function = dasd_3990_erp_overrun;

	DBF_DEV_EVENT(DBF_WARNING, device, "%s",
		    "Overrun - service overrun or overrun"
		    " error requested by channel");

	erp = dasd_3990_erp_action_5(erp);

	return erp;

}