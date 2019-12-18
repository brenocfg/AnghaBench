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
struct tape_request {int* cpdata; scalar_t__ cpaddr; int /*<<< orphan*/  op; } ;
struct tape_device {int* modeset_byte; } ;
struct tape_34xx_block_id {int block; int /*<<< orphan*/  format; } ;

/* Variables and functions */
 int /*<<< orphan*/  DBF_EXCEPTION (int,char*) ; 
 int EINVAL ; 
 scalar_t__ IS_ERR (struct tape_request*) ; 
 int /*<<< orphan*/  LOCATE ; 
 int /*<<< orphan*/  MODE_SET_DB ; 
 int /*<<< orphan*/  NOP ; 
 int PTR_ERR (struct tape_request*) ; 
 int /*<<< orphan*/  TAPE34XX_FMT_3480 ; 
 int /*<<< orphan*/  TAPE34XX_FMT_3480_XF ; 
 int /*<<< orphan*/  TO_LBL ; 
 int /*<<< orphan*/  tape_34xx_merge_sbid (struct tape_device*,struct tape_34xx_block_id*) ; 
 struct tape_request* tape_alloc_request (int,int) ; 
 int /*<<< orphan*/  tape_ccw_cc (scalar_t__,int /*<<< orphan*/ ,int,int*) ; 
 int /*<<< orphan*/  tape_ccw_end (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int tape_do_io_free (struct tape_device*,struct tape_request*) ; 

__attribute__((used)) static int
tape_34xx_mtseek(struct tape_device *device, int mt_count)
{
	struct tape_request *request;
	struct tape_34xx_block_id *	bid;

	if (mt_count > 0x3fffff) {
		DBF_EXCEPTION(6, "xsee parm\n");
		return -EINVAL;
	}
	request = tape_alloc_request(3, 4);
	if (IS_ERR(request))
		return PTR_ERR(request);

	/* setup ccws */
	request->op = TO_LBL;
	bid         = (struct tape_34xx_block_id *) request->cpdata;
	bid->format = (*device->modeset_byte & 0x08) ?
			TAPE34XX_FMT_3480_XF : TAPE34XX_FMT_3480;
	bid->block  = mt_count;
	tape_34xx_merge_sbid(device, bid);

	tape_ccw_cc(request->cpaddr, MODE_SET_DB, 1, device->modeset_byte);
	tape_ccw_cc(request->cpaddr + 1, LOCATE, 4, request->cpdata);
	tape_ccw_end(request->cpaddr + 2, NOP, 0, NULL);

	/* execute it */
	return tape_do_io_free(device, request);
}