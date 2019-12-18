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
struct TYPE_2__ {int /*<<< orphan*/  work; } ;
struct sdebug_defer {TYPE_1__ ew; int /*<<< orphan*/  hrt; } ;
typedef  enum sdeb_defer_type { ____Placeholder_sdeb_defer_type } sdeb_defer_type ;

/* Variables and functions */
 int SDEB_DEFER_HRT ; 
 int SDEB_DEFER_WQ ; 
 int /*<<< orphan*/  cancel_work_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hrtimer_cancel (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void stop_qc_helper(struct sdebug_defer *sd_dp,
			   enum sdeb_defer_type defer_t)
{
	if (!sd_dp)
		return;
	if (defer_t == SDEB_DEFER_HRT)
		hrtimer_cancel(&sd_dp->hrt);
	else if (defer_t == SDEB_DEFER_WQ)
		cancel_work_sync(&sd_dp->ew.work);
}