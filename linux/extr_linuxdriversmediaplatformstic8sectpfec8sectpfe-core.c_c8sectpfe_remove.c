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
struct platform_device {int dummy; } ;
struct channel_info {int dummy; } ;
struct c8sectpfei {int tsin_count; scalar_t__ c8sectpfeclk; scalar_t__ io; int /*<<< orphan*/  dev; struct channel_info** channel_data; int /*<<< orphan*/ * c8sectpfe; int /*<<< orphan*/  fw_ack; } ;

/* Variables and functions */
 scalar_t__ DMA_CPU_RUN ; 
 scalar_t__ SYS_INPUT_CLKEN ; 
 scalar_t__ SYS_OTHER_CLKEN ; 
 int /*<<< orphan*/  c8sectpfe_debugfs_exit (struct c8sectpfei*) ; 
 int /*<<< orphan*/  c8sectpfe_tuner_unregister_frontend (int /*<<< orphan*/ ,struct c8sectpfei*) ; 
 int /*<<< orphan*/  clk_disable_unprepare (scalar_t__) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  free_input_block (struct c8sectpfei*,struct channel_info*) ; 
 struct c8sectpfei* platform_get_drvdata (struct platform_device*) ; 
 scalar_t__ readl (scalar_t__) ; 
 int /*<<< orphan*/  wait_for_completion (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static int c8sectpfe_remove(struct platform_device *pdev)
{
	struct c8sectpfei *fei = platform_get_drvdata(pdev);
	struct channel_info *channel;
	int i;

	wait_for_completion(&fei->fw_ack);

	c8sectpfe_tuner_unregister_frontend(fei->c8sectpfe[0], fei);

	/*
	 * Now loop through and un-configure each of the InputBlock resources
	 */
	for (i = 0; i < fei->tsin_count; i++) {
		channel = fei->channel_data[i];
		free_input_block(fei, channel);
	}

	c8sectpfe_debugfs_exit(fei);

	dev_info(fei->dev, "Stopping memdma SLIM core\n");
	if (readl(fei->io + DMA_CPU_RUN))
		writel(0x0,  fei->io + DMA_CPU_RUN);

	/* unclock all internal IP's */
	if (readl(fei->io + SYS_INPUT_CLKEN))
		writel(0, fei->io + SYS_INPUT_CLKEN);

	if (readl(fei->io + SYS_OTHER_CLKEN))
		writel(0, fei->io + SYS_OTHER_CLKEN);

	if (fei->c8sectpfeclk)
		clk_disable_unprepare(fei->c8sectpfeclk);

	return 0;
}