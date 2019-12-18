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
struct dasd_ccw_req {struct dasd_ccw_req* (* function ) (struct dasd_ccw_req*,char*) ;struct dasd_device* startdev; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DASD_CQR_FAILED ; 
 char DASD_SENSE_BIT_0 ; 
 char DASD_SIM_SENSE ; 
 int /*<<< orphan*/  DBF_DEBUG ; 
 int /*<<< orphan*/  DBF_DEV_EVENT (int /*<<< orphan*/ ,struct dasd_device*,char*,char*) ; 
 int /*<<< orphan*/  DBF_WARNING ; 
 struct dasd_ccw_req* dasd_3990_erp_action_10_32 (struct dasd_ccw_req*,char*) ; 
 struct dasd_ccw_req* dasd_3990_erp_action_1B_32 (struct dasd_ccw_req*,char*) ; 
 struct dasd_ccw_req* dasd_3990_erp_action_4 (struct dasd_ccw_req*,char*) ; 
 struct dasd_ccw_req* dasd_3990_erp_cleanup (struct dasd_ccw_req*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dasd_3990_erp_compound_retry (struct dasd_ccw_req*,char*) ; 
 int /*<<< orphan*/  dasd_3990_erp_handle_sim (struct dasd_device*,char*) ; 
 struct dasd_ccw_req* dasd_3990_erp_int_req (struct dasd_ccw_req*) ; 
 int /*<<< orphan*/  dev_emerg (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  panic (char*) ; 

__attribute__((used)) static struct dasd_ccw_req *
dasd_3990_erp_inspect_32(struct dasd_ccw_req * erp, char *sense)
{

	struct dasd_device *device = erp->startdev;

	erp->function = dasd_3990_erp_inspect_32;

	/* check for SIM sense data */
	if ((sense[6] & DASD_SIM_SENSE) == DASD_SIM_SENSE)
		dasd_3990_erp_handle_sim(device, sense);

	if (sense[25] & DASD_SENSE_BIT_0) {

		/* compound program action codes (byte25 bit 0 == '1') */
		dasd_3990_erp_compound_retry(erp, sense);

	} else {

		/* single program action codes (byte25 bit 0 == '0') */
		switch (sense[25]) {

		case 0x00:	/* success - use default ERP for retries */
			DBF_DEV_EVENT(DBF_DEBUG, device, "%s",
				    "ERP called for successful request"
				    " - just retry");
			break;

		case 0x01:	/* fatal error */
			dev_err(&device->cdev->dev,
				    "ERP failed for the DASD\n");

			erp = dasd_3990_erp_cleanup(erp, DASD_CQR_FAILED);
			break;

		case 0x02:	/* intervention required */
		case 0x03:	/* intervention required during dual copy */
			erp = dasd_3990_erp_int_req(erp);
			break;

		case 0x0F:  /* length mismatch during update write command
			       internal error 08 - update write command error*/
			dev_err(&device->cdev->dev, "An error occurred in the "
				"DASD device driver, reason=%s\n", "08");

			erp = dasd_3990_erp_cleanup(erp, DASD_CQR_FAILED);
			break;

		case 0x10:  /* logging required for other channel program */
			erp = dasd_3990_erp_action_10_32(erp, sense);
			break;

		case 0x15:	/* next track outside defined extend
				   internal error 07 - The next track is not
				   within the defined storage extent */
			dev_err(&device->cdev->dev,
				"An error occurred in the DASD device driver, "
				"reason=%s\n", "07");

			erp = dasd_3990_erp_cleanup(erp, DASD_CQR_FAILED);
			break;

		case 0x1B:	/* unexpected condition during write */

			erp = dasd_3990_erp_action_1B_32(erp, sense);
			break;

		case 0x1C:	/* invalid data */
			dev_emerg(&device->cdev->dev,
				    "Data recovered during retry with PCI "
				    "fetch mode active\n");

			/* not possible to handle this situation in Linux */
			panic
			    ("Invalid data - No way to inform application "
			     "about the possibly incorrect data");
			break;

		case 0x1D:	/* state-change pending */
			DBF_DEV_EVENT(DBF_WARNING, device, "%s",
				    "A State change pending condition exists "
				    "for the subsystem or device");

			erp = dasd_3990_erp_action_4(erp, sense);
			break;

		case 0x1E:	/* busy */
			DBF_DEV_EVENT(DBF_WARNING, device, "%s",
				    "Busy condition exists "
				    "for the subsystem or device");
                        erp = dasd_3990_erp_action_4(erp, sense);
			break;

		default:	/* all others errors - default erp  */
			break;
		}
	}

	return erp;

}