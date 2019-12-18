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
typedef  int /*<<< orphan*/  u8 ;
typedef  int u32 ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DPAA_ASSERT (int) ; 
 int EACCES ; 
 int EINVAL ; 
 int ENODEV ; 
 int MCR_INIT_PFDR ; 
 int /*<<< orphan*/  MCR_get_rslt (int /*<<< orphan*/ ) ; 
 scalar_t__ MCR_rslt_eaccess (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MCR_rslt_idle (int /*<<< orphan*/ ) ; 
 scalar_t__ MCR_rslt_inval (int /*<<< orphan*/ ) ; 
 scalar_t__ MCR_rslt_ok (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  REG_MCP (int) ; 
 int /*<<< orphan*/  REG_MCR ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  dev_crit (struct device*,char*,...) ; 
 int /*<<< orphan*/  dma_wmb () ; 
 int /*<<< orphan*/  qm_ccsr_in (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qm_ccsr_out (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int qm_init_pfdr(struct device *dev, u32 pfdr_start, u32 num)
{
	u8 rslt = MCR_get_rslt(qm_ccsr_in(REG_MCR));

	DPAA_ASSERT(pfdr_start && !(pfdr_start & 7) && !(num & 7) && num);
	/* Make sure the command interface is 'idle' */
	if (!MCR_rslt_idle(rslt)) {
		dev_crit(dev, "QMAN_MCR isn't idle");
		WARN_ON(1);
	}

	/* Write the MCR command params then the verb */
	qm_ccsr_out(REG_MCP(0), pfdr_start);
	/*
	 * TODO: remove this - it's a workaround for a model bug that is
	 * corrected in more recent versions. We use the workaround until
	 * everyone has upgraded.
	 */
	qm_ccsr_out(REG_MCP(1), pfdr_start + num - 16);
	dma_wmb();
	qm_ccsr_out(REG_MCR, MCR_INIT_PFDR);
	/* Poll for the result */
	do {
		rslt = MCR_get_rslt(qm_ccsr_in(REG_MCR));
	} while (!MCR_rslt_idle(rslt));
	if (MCR_rslt_ok(rslt))
		return 0;
	if (MCR_rslt_eaccess(rslt))
		return -EACCES;
	if (MCR_rslt_inval(rslt))
		return -EINVAL;
	dev_crit(dev, "Unexpected result from MCR_INIT_PFDR: %02x\n", rslt);
	return -ENODEV;
}