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
struct vt_notifier_param {struct vc_data* vc; } ;
struct vc_data {int /*<<< orphan*/  vc_screenbuf; int /*<<< orphan*/  vt_pid; } ;
struct TYPE_2__ {struct vc_data* d; } ;

/* Variables and functions */
 int /*<<< orphan*/  VT_DEALLOCATE ; 
 int /*<<< orphan*/  WARN_CONSOLE_UNLOCKED () ; 
 int /*<<< orphan*/  atomic_notifier_call_chain (int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct vt_notifier_param*) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  put_pid (int /*<<< orphan*/ ) ; 
 TYPE_1__* vc_cons ; 
 scalar_t__ vc_cons_allocated (unsigned int) ; 
 int /*<<< orphan*/  vc_uniscr_set (struct vc_data*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vcs_remove_sysfs (unsigned int) ; 
 int /*<<< orphan*/  visual_deinit (struct vc_data*) ; 
 int /*<<< orphan*/  vt_notifier_list ; 

struct vc_data *vc_deallocate(unsigned int currcons)
{
	struct vc_data *vc = NULL;

	WARN_CONSOLE_UNLOCKED();

	if (vc_cons_allocated(currcons)) {
		struct vt_notifier_param param;

		param.vc = vc = vc_cons[currcons].d;
		atomic_notifier_call_chain(&vt_notifier_list, VT_DEALLOCATE, &param);
		vcs_remove_sysfs(currcons);
		visual_deinit(vc);
		put_pid(vc->vt_pid);
		vc_uniscr_set(vc, NULL);
		kfree(vc->vc_screenbuf);
		vc_cons[currcons].d = NULL;
	}
	return vc;
}