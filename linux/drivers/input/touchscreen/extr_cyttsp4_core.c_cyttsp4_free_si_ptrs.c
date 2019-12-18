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
struct TYPE_2__ {int /*<<< orphan*/  mdata; int /*<<< orphan*/  ddata; int /*<<< orphan*/  opcfg; int /*<<< orphan*/  pcfg; int /*<<< orphan*/  test; int /*<<< orphan*/  cydata; } ;
struct cyttsp4_sysinfo {int /*<<< orphan*/  btn_rec_data; int /*<<< orphan*/  xy_data; int /*<<< orphan*/  xy_mode; int /*<<< orphan*/  btn; TYPE_1__ si_ptrs; } ;
struct cyttsp4 {struct cyttsp4_sysinfo sysinfo; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void cyttsp4_free_si_ptrs(struct cyttsp4 *cd)
{
	struct cyttsp4_sysinfo *si = &cd->sysinfo;

	if (!si)
		return;

	kfree(si->si_ptrs.cydata);
	kfree(si->si_ptrs.test);
	kfree(si->si_ptrs.pcfg);
	kfree(si->si_ptrs.opcfg);
	kfree(si->si_ptrs.ddata);
	kfree(si->si_ptrs.mdata);
	kfree(si->btn);
	kfree(si->xy_mode);
	kfree(si->xy_data);
	kfree(si->btn_rec_data);
}