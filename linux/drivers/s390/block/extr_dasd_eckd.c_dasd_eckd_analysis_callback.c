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
struct dasd_eckd_private {int /*<<< orphan*/  init_cqr_status; } ;
struct dasd_device {struct dasd_eckd_private* private; } ;
struct dasd_ccw_req {struct dasd_device* startdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  dasd_eckd_analysis_evaluation (struct dasd_ccw_req*) ; 
 int /*<<< orphan*/  dasd_kick_device (struct dasd_device*) ; 
 int /*<<< orphan*/  dasd_sfree_request (struct dasd_ccw_req*,struct dasd_device*) ; 

__attribute__((used)) static void dasd_eckd_analysis_callback(struct dasd_ccw_req *init_cqr,
					void *data)
{
	struct dasd_device *device = init_cqr->startdev;
	struct dasd_eckd_private *private = device->private;

	private->init_cqr_status = dasd_eckd_analysis_evaluation(init_cqr);
	dasd_sfree_request(init_cqr, device);
	dasd_kick_device(device);
}