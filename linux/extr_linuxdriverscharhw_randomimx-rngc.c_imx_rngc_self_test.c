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
struct imx_rngc {scalar_t__ err_reg; int /*<<< orphan*/  rng_op_done; scalar_t__ base; } ;

/* Variables and functions */
 int EIO ; 
 int ETIMEDOUT ; 
 int RNGC_CMD_SELF_TEST ; 
 scalar_t__ RNGC_COMMAND ; 
 int /*<<< orphan*/  RNGC_TIMEOUT ; 
 int /*<<< orphan*/  imx_rngc_irq_mask_clear (struct imx_rngc*) ; 
 int /*<<< orphan*/  imx_rngc_irq_unmask (struct imx_rngc*) ; 
 int readl (scalar_t__) ; 
 int wait_for_completion_timeout (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static int imx_rngc_self_test(struct imx_rngc *rngc)
{
	u32 cmd;
	int ret;

	imx_rngc_irq_unmask(rngc);

	/* run self test */
	cmd = readl(rngc->base + RNGC_COMMAND);
	writel(cmd | RNGC_CMD_SELF_TEST, rngc->base + RNGC_COMMAND);

	ret = wait_for_completion_timeout(&rngc->rng_op_done, RNGC_TIMEOUT);
	if (!ret) {
		imx_rngc_irq_mask_clear(rngc);
		return -ETIMEDOUT;
	}

	if (rngc->err_reg != 0)
		return -EIO;

	return 0;
}