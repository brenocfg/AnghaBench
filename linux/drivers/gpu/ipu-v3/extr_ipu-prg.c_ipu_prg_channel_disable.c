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
typedef  int /*<<< orphan*/  u32 ;
struct ipuv3_channel {TYPE_1__* ipu; int /*<<< orphan*/  num; } ;
struct ipu_prg_channel {int enabled; } ;
struct ipu_prg {int /*<<< orphan*/  dev; scalar_t__ regs; struct ipu_prg_channel* chan; } ;
struct TYPE_2__ {struct ipu_prg* prg_priv; } ;

/* Variables and functions */
 scalar_t__ IPU_PRG_CTL ; 
 int /*<<< orphan*/  IPU_PRG_CTL_BYPASS (int) ; 
 scalar_t__ IPU_PRG_REG_UPDATE ; 
 int /*<<< orphan*/  IPU_PRG_REG_UPDATE_REG_UPDATE ; 
 int ipu_prg_ipu_to_prg_chan (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ipu_prg_put_pre (struct ipu_prg*,int) ; 
 int /*<<< orphan*/  pm_runtime_get_sync (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm_runtime_put (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  readl (scalar_t__) ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,scalar_t__) ; 

void ipu_prg_channel_disable(struct ipuv3_channel *ipu_chan)
{
	int prg_chan = ipu_prg_ipu_to_prg_chan(ipu_chan->num);
	struct ipu_prg *prg = ipu_chan->ipu->prg_priv;
	struct ipu_prg_channel *chan;
	u32 val;

	if (prg_chan < 0)
		return;

	chan = &prg->chan[prg_chan];
	if (!chan->enabled)
		return;

	pm_runtime_get_sync(prg->dev);

	val = readl(prg->regs + IPU_PRG_CTL);
	val |= IPU_PRG_CTL_BYPASS(prg_chan);
	writel(val, prg->regs + IPU_PRG_CTL);

	val = IPU_PRG_REG_UPDATE_REG_UPDATE;
	writel(val, prg->regs + IPU_PRG_REG_UPDATE);

	pm_runtime_put(prg->dev);

	ipu_prg_put_pre(prg, prg_chan);

	chan->enabled = false;
}