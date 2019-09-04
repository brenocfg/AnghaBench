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
struct TYPE_2__ {void* src; void* obj; int /*<<< orphan*/  cmd; int /*<<< orphan*/  type; } ;
union hi6220_mbox_data {TYPE_1__ msg; } ;
struct hi6220_stub_clk {int /*<<< orphan*/  mbox; int /*<<< orphan*/  dfs_map; } ;

/* Variables and functions */
 int /*<<< orphan*/  ACPU_DFS_FREQ_REQ ; 
 int /*<<< orphan*/  HI6220_MBOX_CMD_SET ; 
 int /*<<< orphan*/  HI6220_MBOX_FREQ ; 
 void* HI6220_MBOX_OBJ_AP ; 
 int /*<<< orphan*/  mbox_send_message (int /*<<< orphan*/ ,union hi6220_mbox_data*) ; 
 int /*<<< orphan*/  regmap_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int) ; 

__attribute__((used)) static int hi6220_acpu_set_freq(struct hi6220_stub_clk *stub_clk,
				unsigned int freq)
{
	union hi6220_mbox_data data;

	/* set the frequency in sram */
	regmap_write(stub_clk->dfs_map, ACPU_DFS_FREQ_REQ, freq);

	/* compound mailbox message */
	data.msg.type = HI6220_MBOX_FREQ;
	data.msg.cmd  = HI6220_MBOX_CMD_SET;
	data.msg.obj  = HI6220_MBOX_OBJ_AP;
	data.msg.src  = HI6220_MBOX_OBJ_AP;

	mbox_send_message(stub_clk->mbox, &data);
	return 0;
}