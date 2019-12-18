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
struct tape_request {scalar_t__ cpaddr; int /*<<< orphan*/  op; } ;
struct tape_device {int* modeset_byte; } ;

/* Variables and functions */
 int /*<<< orphan*/  DBF_EXCEPTION (int,char*) ; 
 int EINVAL ; 
 scalar_t__ IS_ERR (struct tape_request*) ; 
 int /*<<< orphan*/  MODE_SET_DB ; 
 int /*<<< orphan*/  NOP ; 
 int PTR_ERR (struct tape_request*) ; 
 int /*<<< orphan*/  TO_NOP ; 
 struct tape_request* tape_alloc_request (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tape_ccw_cc (scalar_t__,int /*<<< orphan*/ ,int,int*) ; 
 int /*<<< orphan*/  tape_ccw_end (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int tape_do_io_free (struct tape_device*,struct tape_request*) ; 

int
tape_std_mtcompression(struct tape_device *device, int mt_count)
{
	struct tape_request *request;

	if (mt_count < 0 || mt_count > 1) {
		DBF_EXCEPTION(6, "xcom parm\n");
		return -EINVAL;
	}
	request = tape_alloc_request(2, 0);
	if (IS_ERR(request))
		return PTR_ERR(request);
	request->op = TO_NOP;
	/* setup ccws */
	if (mt_count == 0)
		*device->modeset_byte &= ~0x08;
	else
		*device->modeset_byte |= 0x08;
	tape_ccw_cc(request->cpaddr, MODE_SET_DB, 1, device->modeset_byte);
	tape_ccw_end(request->cpaddr + 1, NOP, 0, NULL);
	/* execute it */
	return tape_do_io_free(device, request);
}