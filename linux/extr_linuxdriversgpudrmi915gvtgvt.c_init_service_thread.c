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
struct intel_gvt {int /*<<< orphan*/  service_thread; int /*<<< orphan*/  service_thread_wq; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gvt_err (char*) ; 
 int /*<<< orphan*/  gvt_service_thread ; 
 int /*<<< orphan*/  init_waitqueue_head (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kthread_run (int /*<<< orphan*/ ,struct intel_gvt*,char*) ; 

__attribute__((used)) static int init_service_thread(struct intel_gvt *gvt)
{
	init_waitqueue_head(&gvt->service_thread_wq);

	gvt->service_thread = kthread_run(gvt_service_thread,
			gvt, "gvt_service_thread");
	if (IS_ERR(gvt->service_thread)) {
		gvt_err("fail to start service thread.\n");
		return PTR_ERR(gvt->service_thread);
	}
	return 0;
}