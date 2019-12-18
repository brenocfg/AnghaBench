#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int count; scalar_t__ cda; int /*<<< orphan*/  flags; int /*<<< orphan*/  cmd_code; } ;
struct TYPE_4__ {int /*<<< orphan*/  callback; TYPE_1__ ccw; scalar_t__ view; } ;
struct raw3270 {scalar_t__ state; TYPE_2__ init_reset; int /*<<< orphan*/  init_view; int /*<<< orphan*/ * init_data; } ;
typedef  scalar_t__ __u32 ;

/* Variables and functions */
 int /*<<< orphan*/  CCW_FLAG_SLI ; 
 int EBUSY ; 
 scalar_t__ RAW3270_STATE_INIT ; 
 scalar_t__ RAW3270_STATE_RESET ; 
 int /*<<< orphan*/  TC_EWRITEA ; 
 int /*<<< orphan*/  TW_KR ; 
 scalar_t__ __pa (int /*<<< orphan*/ *) ; 
 int __raw3270_start (struct raw3270*,int /*<<< orphan*/ *,TYPE_2__*) ; 
 int /*<<< orphan*/  raw3270_reset_device_cb ; 

__attribute__((used)) static int
__raw3270_reset_device(struct raw3270 *rp)
{
	int rc;

	/* Check if reset is already pending */
	if (rp->init_reset.view)
		return -EBUSY;
	/* Store reset data stream to init_data/init_reset */
	rp->init_data[0] = TW_KR;
	rp->init_reset.ccw.cmd_code = TC_EWRITEA;
	rp->init_reset.ccw.flags = CCW_FLAG_SLI;
	rp->init_reset.ccw.count = 1;
	rp->init_reset.ccw.cda = (__u32) __pa(rp->init_data);
	rp->init_reset.callback = raw3270_reset_device_cb;
	rc = __raw3270_start(rp, &rp->init_view, &rp->init_reset);
	if (rc == 0 && rp->state == RAW3270_STATE_INIT)
		rp->state = RAW3270_STATE_RESET;
	return rc;
}