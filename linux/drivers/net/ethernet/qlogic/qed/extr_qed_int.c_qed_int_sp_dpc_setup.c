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
struct qed_hwfn {int b_sp_dpc_enabled; int /*<<< orphan*/  sp_dpc; } ;

/* Variables and functions */
 int /*<<< orphan*/  qed_int_sp_dpc ; 
 int /*<<< orphan*/  tasklet_init (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned long) ; 

__attribute__((used)) static void qed_int_sp_dpc_setup(struct qed_hwfn *p_hwfn)
{
	tasklet_init(p_hwfn->sp_dpc,
		     qed_int_sp_dpc, (unsigned long)p_hwfn);
	p_hwfn->b_sp_dpc_enabled = true;
}