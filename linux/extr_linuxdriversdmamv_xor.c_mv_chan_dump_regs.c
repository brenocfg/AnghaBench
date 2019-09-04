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
typedef  int /*<<< orphan*/  u32 ;
struct mv_xor_chan {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  XOR_ACTIVATION (struct mv_xor_chan*) ; 
 int /*<<< orphan*/  XOR_CONFIG (struct mv_xor_chan*) ; 
 int /*<<< orphan*/  XOR_ERROR_ADDR (struct mv_xor_chan*) ; 
 int /*<<< orphan*/  XOR_ERROR_CAUSE (struct mv_xor_chan*) ; 
 int /*<<< orphan*/  XOR_INTR_CAUSE (struct mv_xor_chan*) ; 
 int /*<<< orphan*/  XOR_INTR_MASK (struct mv_xor_chan*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mv_chan_to_devp (struct mv_xor_chan*) ; 
 int /*<<< orphan*/  readl_relaxed (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void mv_chan_dump_regs(struct mv_xor_chan *chan)
{
	u32 val;

	val = readl_relaxed(XOR_CONFIG(chan));
	dev_err(mv_chan_to_devp(chan), "config       0x%08x\n", val);

	val = readl_relaxed(XOR_ACTIVATION(chan));
	dev_err(mv_chan_to_devp(chan), "activation   0x%08x\n", val);

	val = readl_relaxed(XOR_INTR_CAUSE(chan));
	dev_err(mv_chan_to_devp(chan), "intr cause   0x%08x\n", val);

	val = readl_relaxed(XOR_INTR_MASK(chan));
	dev_err(mv_chan_to_devp(chan), "intr mask    0x%08x\n", val);

	val = readl_relaxed(XOR_ERROR_CAUSE(chan));
	dev_err(mv_chan_to_devp(chan), "error cause  0x%08x\n", val);

	val = readl_relaxed(XOR_ERROR_ADDR(chan));
	dev_err(mv_chan_to_devp(chan), "error addr   0x%08x\n", val);
}