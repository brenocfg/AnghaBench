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
struct fc_lport {scalar_t__ state; int /*<<< orphan*/  qfull; scalar_t__ link_up; } ;

/* Variables and functions */
 scalar_t__ LPORT_ST_READY ; 

__attribute__((used)) static inline int fc_fcp_lport_queue_ready(struct fc_lport *lport)
{
	/* lock ? */
	return (lport->state == LPORT_ST_READY) &&
		lport->link_up && !lport->qfull;
}