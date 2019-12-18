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
struct dasd_ccw_req {char status; int /*<<< orphan*/  memdev; struct dasd_ccw_req* refers; } ;

/* Variables and functions */
 int /*<<< orphan*/  dasd_free_erp_request (struct dasd_ccw_req*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct dasd_ccw_req *
dasd_3990_erp_cleanup(struct dasd_ccw_req * erp, char final_status)
{
	struct dasd_ccw_req *cqr = erp->refers;

	dasd_free_erp_request(erp, erp->memdev);
	cqr->status = final_status;
	return cqr;

}