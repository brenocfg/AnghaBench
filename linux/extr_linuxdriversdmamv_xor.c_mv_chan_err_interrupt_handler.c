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
typedef  int u32 ;
struct mv_xor_chan {int /*<<< orphan*/  idx; } ;

/* Variables and functions */
 int /*<<< orphan*/  WARN_ON (int) ; 
 int XOR_INT_ERR_DECODE ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mv_chan_dump_regs (struct mv_xor_chan*) ; 
 int /*<<< orphan*/  mv_chan_to_devp (struct mv_xor_chan*) ; 

__attribute__((used)) static void mv_chan_err_interrupt_handler(struct mv_xor_chan *chan,
					  u32 intr_cause)
{
	if (intr_cause & XOR_INT_ERR_DECODE) {
		dev_dbg(mv_chan_to_devp(chan), "ignoring address decode error\n");
		return;
	}

	dev_err(mv_chan_to_devp(chan), "error on chan %d. intr cause 0x%08x\n",
		chan->idx, intr_cause);

	mv_chan_dump_regs(chan);
	WARN_ON(1);
}