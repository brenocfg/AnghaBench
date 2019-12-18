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
struct dasd_ccw_req {int retries; struct dasd_ccw_req* (* function ) (struct dasd_ccw_req*,char*) ;} ;

/* Variables and functions */
 char DASD_SENSE_BIT_2 ; 
 int HZ ; 
 struct dasd_ccw_req* dasd_3990_erp_DCTL (struct dasd_ccw_req*,int) ; 
 int /*<<< orphan*/  dasd_3990_erp_block_queue (struct dasd_ccw_req*,int) ; 

__attribute__((used)) static struct dasd_ccw_req *
dasd_3990_erp_compound_code(struct dasd_ccw_req * erp, char *sense)
{

	if (sense[25] & DASD_SENSE_BIT_2) {

		switch (sense[28]) {
		case 0x17:
			/* issue a Diagnostic Control command with an
			 * Inhibit Write subcommand and controller modifier */
			erp = dasd_3990_erp_DCTL(erp, 0x20);
			break;

		case 0x25:
			/* wait for 5 seconds and retry again */
			erp->retries = 1;

			dasd_3990_erp_block_queue (erp, 5*HZ);
			break;

		default:
			/* should not happen - continue */
			break;
		}
	}

	erp->function = dasd_3990_erp_compound_code;

	return erp;

}