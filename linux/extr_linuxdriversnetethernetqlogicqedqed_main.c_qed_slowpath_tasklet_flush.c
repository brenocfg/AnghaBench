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
struct qed_hwfn {int /*<<< orphan*/  sp_dpc; scalar_t__ b_sp_dpc_enabled; } ;

/* Variables and functions */
 int /*<<< orphan*/  tasklet_disable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tasklet_enable (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void qed_slowpath_tasklet_flush(struct qed_hwfn *p_hwfn)
{
	/* Calling the disable function will make sure that any
	 * currently-running function is completed. The following call to the
	 * enable function makes this sequence a flush-like operation.
	 */
	if (p_hwfn->b_sp_dpc_enabled) {
		tasklet_disable(p_hwfn->sp_dpc);
		tasklet_enable(p_hwfn->sp_dpc);
	}
}