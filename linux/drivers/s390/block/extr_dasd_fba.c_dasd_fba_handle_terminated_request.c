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
struct dasd_ccw_req {scalar_t__ retries; int /*<<< orphan*/  status; } ;

/* Variables and functions */
 int /*<<< orphan*/  DASD_CQR_FAILED ; 
 int /*<<< orphan*/  DASD_CQR_FILLED ; 

__attribute__((used)) static void dasd_fba_handle_terminated_request(struct dasd_ccw_req *cqr)
{
	if (cqr->retries < 0)
		cqr->status = DASD_CQR_FAILED;
	else
		cqr->status = DASD_CQR_FILLED;
}