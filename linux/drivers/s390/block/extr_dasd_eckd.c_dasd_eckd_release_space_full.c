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
struct dasd_ccw_req {int /*<<< orphan*/  memdev; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (struct dasd_ccw_req*) ; 
 int PTR_ERR (struct dasd_ccw_req*) ; 
 struct dasd_ccw_req* dasd_eckd_dso_ras (struct dasd_device*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dasd_sfree_request (struct dasd_ccw_req*,int /*<<< orphan*/ ) ; 
 int dasd_sleep_on_interruptible (struct dasd_ccw_req*) ; 

__attribute__((used)) static int dasd_eckd_release_space_full(struct dasd_device *device)
{
	struct dasd_ccw_req *cqr;
	int rc;

	cqr = dasd_eckd_dso_ras(device, NULL, NULL, 0, 0, 0);
	if (IS_ERR(cqr))
		return PTR_ERR(cqr);

	rc = dasd_sleep_on_interruptible(cqr);

	dasd_sfree_request(cqr, cqr->memdev);

	return rc;
}