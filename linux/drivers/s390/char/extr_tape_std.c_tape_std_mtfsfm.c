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
struct tape_request {int /*<<< orphan*/  cpaddr; int /*<<< orphan*/  op; } ;
struct tape_device {int /*<<< orphan*/  modeset_byte; } ;
struct ccw1 {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  FORSPACEFILE ; 
 scalar_t__ IS_ERR (struct tape_request*) ; 
 int /*<<< orphan*/  MODE_SET_DB ; 
 int /*<<< orphan*/  MTBSR ; 
 int /*<<< orphan*/  NOP ; 
 int PTR_ERR (struct tape_request*) ; 
 int /*<<< orphan*/  TO_FSF ; 
 struct tape_request* tape_alloc_request (int,int /*<<< orphan*/ ) ; 
 struct ccw1* tape_ccw_cc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 struct ccw1* tape_ccw_end (struct ccw1*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct ccw1* tape_ccw_repeat (struct ccw1*,int /*<<< orphan*/ ,int) ; 
 int tape_do_io_free (struct tape_device*,struct tape_request*) ; 
 int tape_mtop (struct tape_device*,int /*<<< orphan*/ ,int) ; 

int
tape_std_mtfsfm(struct tape_device *device, int mt_count)
{
	struct tape_request *request;
	struct ccw1 *ccw;
	int rc;

	request = tape_alloc_request(mt_count + 2, 0);
	if (IS_ERR(request))
		return PTR_ERR(request);
	request->op = TO_FSF;
	/* setup ccws */
	ccw = tape_ccw_cc(request->cpaddr, MODE_SET_DB, 1,
			  device->modeset_byte);
	ccw = tape_ccw_repeat(ccw, FORSPACEFILE, mt_count);
	ccw = tape_ccw_end(ccw, NOP, 0, NULL);
	/* execute it */
	rc = tape_do_io_free(device, request);
	if (rc == 0) {
		rc = tape_mtop(device, MTBSR, 1);
		if (rc > 0)
			rc = 0;
	}

	return rc;
}