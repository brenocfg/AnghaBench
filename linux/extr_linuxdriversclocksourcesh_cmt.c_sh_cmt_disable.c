#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct sh_cmt_channel {TYPE_2__* cmt; } ;
struct TYPE_4__ {TYPE_1__* pdev; int /*<<< orphan*/  clk; } ;
struct TYPE_3__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  clk_disable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_pm_syscore_device (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  pm_runtime_put (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sh_cmt_start_stop_ch (struct sh_cmt_channel*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sh_cmt_write_cmcsr (struct sh_cmt_channel*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void sh_cmt_disable(struct sh_cmt_channel *ch)
{
	/* disable channel */
	sh_cmt_start_stop_ch(ch, 0);

	/* disable interrupts in CMT block */
	sh_cmt_write_cmcsr(ch, 0);

	/* stop clock */
	clk_disable(ch->cmt->clk);

	dev_pm_syscore_device(&ch->cmt->pdev->dev, false);
	pm_runtime_put(&ch->cmt->pdev->dev);
}