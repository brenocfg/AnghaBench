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
typedef  int u8 ;
struct irb {int /*<<< orphan*/  scsw; } ;
struct dasd_device {int dummy; } ;
struct dasd_ccw_req {int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  DASD_CQR_SUPPRESS_CR ; 
 int /*<<< orphan*/  DASD_CQR_SUPPRESS_FP ; 
 int /*<<< orphan*/  DASD_CQR_SUPPRESS_IL ; 
 int /*<<< orphan*/  DASD_CQR_SUPPRESS_NRF ; 
 int SNS0_CMD_REJECT ; 
 int SNS1_FILE_PROTECTED ; 
 int SNS1_NO_REC_FOUND ; 
 int /*<<< orphan*/  dasd_eckd_dump_sense_ccw (struct dasd_device*,struct dasd_ccw_req*,struct irb*) ; 
 int /*<<< orphan*/  dasd_eckd_dump_sense_tcw (struct dasd_device*,struct dasd_ccw_req*,struct irb*) ; 
 int* dasd_get_sense (struct irb*) ; 
 int scsw_cstat (int /*<<< orphan*/ *) ; 
 scalar_t__ scsw_is_tm (int /*<<< orphan*/ *) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void dasd_eckd_dump_sense(struct dasd_device *device,
				 struct dasd_ccw_req *req, struct irb *irb)
{
	u8 *sense = dasd_get_sense(irb);

	if (scsw_is_tm(&irb->scsw)) {
		/*
		 * In some cases the 'File Protected' or 'Incorrect Length'
		 * error might be expected and log messages shouldn't be written
		 * then. Check if the according suppress bit is set.
		 */
		if (sense && (sense[1] & SNS1_FILE_PROTECTED) &&
		    test_bit(DASD_CQR_SUPPRESS_FP, &req->flags))
			return;
		if (scsw_cstat(&irb->scsw) == 0x40 &&
		    test_bit(DASD_CQR_SUPPRESS_IL, &req->flags))
			return;

		dasd_eckd_dump_sense_tcw(device, req, irb);
	} else {
		/*
		 * In some cases the 'Command Reject' or 'No Record Found'
		 * error might be expected and log messages shouldn't be
		 * written then. Check if the according suppress bit is set.
		 */
		if (sense && sense[0] & SNS0_CMD_REJECT &&
		    test_bit(DASD_CQR_SUPPRESS_CR, &req->flags))
			return;

		if (sense && sense[1] & SNS1_NO_REC_FOUND &&
		    test_bit(DASD_CQR_SUPPRESS_NRF, &req->flags))
			return;

		dasd_eckd_dump_sense_ccw(device, req, irb);
	}
}