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
struct rvt_dev_info {int /*<<< orphan*/  ibdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  ib_unregister_device (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rvt_free_mad_agents (struct rvt_dev_info*) ; 
 int /*<<< orphan*/  rvt_mr_exit (struct rvt_dev_info*) ; 
 int /*<<< orphan*/  rvt_qp_exit (struct rvt_dev_info*) ; 
 int /*<<< orphan*/  rvt_wss_exit (struct rvt_dev_info*) ; 
 int /*<<< orphan*/  trace_rvt_dbg (struct rvt_dev_info*,char*) ; 

void rvt_unregister_device(struct rvt_dev_info *rdi)
{
	trace_rvt_dbg(rdi, "Driver is unregistering.");
	if (!rdi)
		return;

	rvt_free_mad_agents(rdi);

	ib_unregister_device(&rdi->ibdev);
	rvt_wss_exit(rdi);
	rvt_mr_exit(rdi);
	rvt_qp_exit(rdi);
}