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
struct dasd_ccw_req {int /*<<< orphan*/  block; } ;

/* Variables and functions */
 int /*<<< orphan*/  dasd_schedule_block_bh (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void dasd_return_cqr_cb(struct dasd_ccw_req *cqr, void *data)
{
	dasd_schedule_block_bh(cqr->block);
}