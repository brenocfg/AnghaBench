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
struct cpt_vf {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  cleanup_command_queues (struct cpt_vf*) ; 
 int /*<<< orphan*/  cleanup_pending_queues (struct cpt_vf*) ; 
 int /*<<< orphan*/  cleanup_worker_threads (struct cpt_vf*) ; 

__attribute__((used)) static void cptvf_sw_cleanup(struct cpt_vf *cptvf)
{
	cleanup_worker_threads(cptvf);
	cleanup_pending_queues(cptvf);
	cleanup_command_queues(cptvf);
}