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
struct dasd_device {TYPE_1__* cdev; } ;
struct dasd_ccw_req {void (* function ) (struct dasd_ccw_req*,char*) ;struct dasd_device* startdev; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 char DASD_SENSE_BIT_1 ; 
 char DASD_SENSE_BIT_2 ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,char*) ; 

__attribute__((used)) static void
dasd_3990_erp_compound_config(struct dasd_ccw_req * erp, char *sense)
{

	if ((sense[25] & DASD_SENSE_BIT_1) && (sense[26] & DASD_SENSE_BIT_2)) {

		/* set to suspended duplex state then restart
		   internal error 05 - Set device to suspended duplex state
		   should be done */
		struct dasd_device *device = erp->startdev;
		dev_err(&device->cdev->dev,
			"An error occurred in the DASD device driver, "
			"reason=%s\n", "05");

	}

	erp->function = dasd_3990_erp_compound_config;

}