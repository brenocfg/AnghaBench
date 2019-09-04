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
struct dvb_frontend {TYPE_1__* dvb; } ;
struct dvb_diseqc_master_cmd {int /*<<< orphan*/  msg; int /*<<< orphan*/  msg_len; } ;
struct budget_patch {int dummy; } ;
struct TYPE_2__ {scalar_t__ priv; } ;

/* Variables and functions */
 int /*<<< orphan*/  av7110_send_diseqc_msg (struct budget_patch*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int budget_patch_diseqc_send_master_cmd(struct dvb_frontend* fe, struct dvb_diseqc_master_cmd* cmd)
{
	struct budget_patch* budget = (struct budget_patch*) fe->dvb->priv;

	av7110_send_diseqc_msg (budget, cmd->msg_len, cmd->msg, 0);

	return 0;
}