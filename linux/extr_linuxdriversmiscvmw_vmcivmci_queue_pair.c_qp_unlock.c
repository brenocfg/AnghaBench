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
struct vmci_qp {int /*<<< orphan*/  produce_q; } ;

/* Variables and functions */
 int /*<<< orphan*/  qp_release_queue_mutex (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void qp_unlock(const struct vmci_qp *qpair)
{
	qp_release_queue_mutex(qpair->produce_q);
}