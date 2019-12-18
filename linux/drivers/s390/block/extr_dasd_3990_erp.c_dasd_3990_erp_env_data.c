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
struct dasd_ccw_req {int /*<<< orphan*/  status; struct dasd_ccw_req* (* function ) (struct dasd_ccw_req*,char*) ;struct dasd_device* startdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DASD_CQR_FILLED ; 
 int /*<<< orphan*/  DBF_DEV_EVENT (int /*<<< orphan*/ ,struct dasd_device*,char*,char*) ; 
 int /*<<< orphan*/  DBF_WARNING ; 
 struct dasd_ccw_req* dasd_3990_erp_action_4 (struct dasd_ccw_req*,char*) ; 
 int /*<<< orphan*/  dasd_3990_handle_env_data (struct dasd_ccw_req*,char*) ; 

__attribute__((used)) static struct dasd_ccw_req *
dasd_3990_erp_env_data(struct dasd_ccw_req * erp, char *sense)
{

	struct dasd_device *device = erp->startdev;

	erp->function = dasd_3990_erp_env_data;

	DBF_DEV_EVENT(DBF_WARNING, device, "%s", "Environmental data present");

	dasd_3990_handle_env_data(erp, sense);

	/* don't retry on disabled interface */
	if (sense[7] != 0x0F) {
		erp = dasd_3990_erp_action_4(erp, sense);
	} else {
		erp->status = DASD_CQR_FILLED;
	}

	return erp;

}