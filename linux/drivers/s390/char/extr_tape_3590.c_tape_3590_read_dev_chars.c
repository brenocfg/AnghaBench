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
struct tape_request {int /*<<< orphan*/  cpdata; int /*<<< orphan*/  cpaddr; int /*<<< orphan*/  op; } ;
struct tape_device {int dummy; } ;
struct tape_3590_rdc_data {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CCW_CMD_RDC ; 
 scalar_t__ IS_ERR (struct tape_request*) ; 
 int PTR_ERR (struct tape_request*) ; 
 int /*<<< orphan*/  TO_RDC ; 
 int /*<<< orphan*/  memcpy (struct tape_3590_rdc_data*,int /*<<< orphan*/ ,int) ; 
 struct tape_request* tape_alloc_request (int,int) ; 
 int /*<<< orphan*/  tape_ccw_end (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int tape_do_io (struct tape_device*,struct tape_request*) ; 
 int /*<<< orphan*/  tape_free_request (struct tape_request*) ; 

__attribute__((used)) static int tape_3590_read_dev_chars(struct tape_device *device,
				    struct tape_3590_rdc_data *rdc_data)
{
	int rc;
	struct tape_request *request;

	request = tape_alloc_request(1, sizeof(*rdc_data));
	if (IS_ERR(request))
		return PTR_ERR(request);
	request->op = TO_RDC;
	tape_ccw_end(request->cpaddr, CCW_CMD_RDC, sizeof(*rdc_data),
		     request->cpdata);
	rc = tape_do_io(device, request);
	if (rc == 0)
		memcpy(rdc_data, request->cpdata, sizeof(*rdc_data));
	tape_free_request(request);
	return rc;
}