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
struct nvme_fc_rport {struct nvme_fc_lport* lport; } ;
struct nvme_fc_lport {int /*<<< orphan*/  act_rport_cnt; } ;

/* Variables and functions */
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
nvme_fc_rport_active_on_lport(struct nvme_fc_rport *rport)
{
	struct nvme_fc_lport *lport = rport->lport;

	atomic_inc(&lport->act_rport_cnt);
}