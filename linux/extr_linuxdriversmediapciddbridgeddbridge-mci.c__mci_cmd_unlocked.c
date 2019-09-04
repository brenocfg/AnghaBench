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
typedef  int u32 ;
struct mci {int /*<<< orphan*/  nr; TYPE_1__* base; } ;
struct ddb_link {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; int /*<<< orphan*/  completion; struct ddb_link* link; } ;

/* Variables and functions */
 int EIO ; 
 int /*<<< orphan*/  HZ ; 
 scalar_t__ MCI_COMMAND ; 
 scalar_t__ MCI_CONTROL ; 
 int MCI_CONTROL_ENABLE_DONE_INTERRUPT ; 
 int MCI_CONTROL_RESET ; 
 int MCI_CONTROL_START_COMMAND ; 
 scalar_t__ MCI_RESULT ; 
 int ddblreadl (struct ddb_link*,scalar_t__) ; 
 int /*<<< orphan*/  ddblwritel (struct ddb_link*,int,scalar_t__) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 unsigned long wait_for_completion_timeout (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int _mci_cmd_unlocked(struct mci *state,
			     u32 *cmd, u32 cmd_len,
			     u32 *res, u32 res_len)
{
	struct ddb_link *link = state->base->link;
	u32 i, val;
	unsigned long stat;

	val = ddblreadl(link, MCI_CONTROL);
	if (val & (MCI_CONTROL_RESET | MCI_CONTROL_START_COMMAND))
		return -EIO;
	if (cmd && cmd_len)
		for (i = 0; i < cmd_len; i++)
			ddblwritel(link, cmd[i], MCI_COMMAND + i * 4);
	val |= (MCI_CONTROL_START_COMMAND | MCI_CONTROL_ENABLE_DONE_INTERRUPT);
	ddblwritel(link, val, MCI_CONTROL);

	stat = wait_for_completion_timeout(&state->base->completion, HZ);
	if (stat == 0) {
		dev_warn(state->base->dev, "MCI-%d: MCI timeout\n", state->nr);
		return -EIO;
	}
	if (res && res_len)
		for (i = 0; i < res_len; i++)
			res[i] = ddblreadl(link, MCI_RESULT + i * 4);
	return 0;
}