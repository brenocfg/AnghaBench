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
struct ehea_port_res {int sq_skba_size; int swqe_ll_count; int /*<<< orphan*/  swqe_avail; } ;
struct ehea_port {int num_def_qps; int /*<<< orphan*/  swqe_avail_wq; struct ehea_port_res* port_res; } ;

/* Variables and functions */
 int atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  msecs_to_jiffies (int) ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 int wait_event_timeout (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ehea_flush_sq(struct ehea_port *port)
{
	int i;

	for (i = 0; i < port->num_def_qps; i++) {
		struct ehea_port_res *pr = &port->port_res[i];
		int swqe_max = pr->sq_skba_size - 2 - pr->swqe_ll_count;
		int ret;

		ret = wait_event_timeout(port->swqe_avail_wq,
			 atomic_read(&pr->swqe_avail) >= swqe_max,
			 msecs_to_jiffies(100));

		if (!ret) {
			pr_err("WARNING: sq not flushed completely\n");
			break;
		}
	}
}