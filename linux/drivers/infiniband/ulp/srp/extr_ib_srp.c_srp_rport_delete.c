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
struct srp_target_port {int dummy; } ;
struct srp_rport {struct srp_target_port* lld_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  srp_queue_remove_work (struct srp_target_port*) ; 

__attribute__((used)) static void srp_rport_delete(struct srp_rport *rport)
{
	struct srp_target_port *target = rport->lld_data;

	srp_queue_remove_work(target);
}