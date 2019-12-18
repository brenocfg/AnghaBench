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
struct dasd_ccw_req {int /*<<< orphan*/  flags; struct dasd_device* startdev; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DASD_CQR_FAILED ; 
 int /*<<< orphan*/  DASD_CQR_SUPPRESS_FP ; 
 struct dasd_ccw_req* dasd_3990_erp_cleanup (struct dasd_ccw_req*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static struct dasd_ccw_req *
dasd_3990_erp_file_prot(struct dasd_ccw_req * erp)
{

	struct dasd_device *device = erp->startdev;

	/*
	 * In some cases the 'File Protected' error might be expected and
	 * log messages shouldn't be written then.
	 * Check if the according suppress bit is set.
	 */
	if (!test_bit(DASD_CQR_SUPPRESS_FP, &erp->flags))
		dev_err(&device->cdev->dev,
			"Accessing the DASD failed because of a hardware error\n");

	return dasd_3990_erp_cleanup(erp, DASD_CQR_FAILED);

}