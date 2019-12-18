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
struct raw3270_request {scalar_t__ rc; TYPE_1__* view; } ;
struct raw3270 {scalar_t__ state; int /*<<< orphan*/  init_reset; } ;
struct TYPE_2__ {struct raw3270* dev; } ;

/* Variables and functions */
 scalar_t__ MACHINE_IS_VM ; 
 scalar_t__ RAW3270_STATE_INIT ; 
 scalar_t__ RAW3270_STATE_RESET ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  raw3270_size_device_done (struct raw3270*) ; 
 int /*<<< orphan*/  raw3270_size_device_vm (struct raw3270*) ; 
 int /*<<< orphan*/  raw3270_writesf_readpart (struct raw3270*) ; 

__attribute__((used)) static void
raw3270_reset_device_cb(struct raw3270_request *rq, void *data)
{
	struct raw3270 *rp = rq->view->dev;

	if (rp->state != RAW3270_STATE_RESET)
		return;
	if (rq->rc) {
		/* Reset command failed. */
		rp->state = RAW3270_STATE_INIT;
	} else if (MACHINE_IS_VM) {
		raw3270_size_device_vm(rp);
		raw3270_size_device_done(rp);
	} else
		raw3270_writesf_readpart(rp);
	memset(&rp->init_reset, 0, sizeof(rp->init_reset));
}