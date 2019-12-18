#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_6__ {scalar_t__ ret; } ;
struct TYPE_5__ {int size; struct tegra_bpmp_message* data; } ;
struct TYPE_4__ {int /*<<< orphan*/  state; } ;
struct tegra_bpmp_message {unsigned int id; TYPE_3__ rx; TYPE_2__ tx; int /*<<< orphan*/  mrq; TYPE_1__ set_state; int /*<<< orphan*/  cmd; } ;
struct tegra_bpmp {int dummy; } ;
struct mrq_pg_request {unsigned int id; TYPE_3__ rx; TYPE_2__ tx; int /*<<< orphan*/  mrq; TYPE_1__ set_state; int /*<<< orphan*/  cmd; } ;
typedef  int /*<<< orphan*/  request ;
typedef  int /*<<< orphan*/  msg ;

/* Variables and functions */
 int /*<<< orphan*/  CMD_PG_SET_STATE ; 
 int EINVAL ; 
 int /*<<< orphan*/  MRQ_PG ; 
 int /*<<< orphan*/  memset (struct tegra_bpmp_message*,int /*<<< orphan*/ ,int) ; 
 int tegra_bpmp_transfer (struct tegra_bpmp*,struct tegra_bpmp_message*) ; 

__attribute__((used)) static int tegra_bpmp_powergate_set_state(struct tegra_bpmp *bpmp,
					  unsigned int id, u32 state)
{
	struct mrq_pg_request request;
	struct tegra_bpmp_message msg;
	int err;

	memset(&request, 0, sizeof(request));
	request.cmd = CMD_PG_SET_STATE;
	request.id = id;
	request.set_state.state = state;

	memset(&msg, 0, sizeof(msg));
	msg.mrq = MRQ_PG;
	msg.tx.data = &request;
	msg.tx.size = sizeof(request);

	err = tegra_bpmp_transfer(bpmp, &msg);
	if (err < 0)
		return err;
	else if (msg.rx.ret < 0)
		return -EINVAL;

	return 0;
}