#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_5__ {struct tegra_hsp* hsp; } ;
struct tegra_hsp_doorbell {scalar_t__ master; TYPE_2__ channel; } ;
struct tegra_hsp {int /*<<< orphan*/  lock; } ;
struct mbox_chan {TYPE_1__* mbox; struct tegra_hsp_doorbell* con_priv; } ;
struct TYPE_4__ {scalar_t__ num_chans; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  BIT (scalar_t__) ; 
 int EINVAL ; 
 int ENODEV ; 
 int /*<<< orphan*/  HSP_DB_ENABLE ; 
 int /*<<< orphan*/  TEGRA_HSP_DB_MASTER_CCPLEX ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,scalar_t__) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  tegra_hsp_channel_readl (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tegra_hsp_channel_writel (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tegra_hsp_doorbell_can_ring (struct tegra_hsp_doorbell*) ; 
 struct tegra_hsp_doorbell* tegra_hsp_doorbell_get (struct tegra_hsp*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int tegra_hsp_doorbell_startup(struct mbox_chan *chan)
{
	struct tegra_hsp_doorbell *db = chan->con_priv;
	struct tegra_hsp *hsp = db->channel.hsp;
	struct tegra_hsp_doorbell *ccplex;
	unsigned long flags;
	u32 value;

	if (db->master >= chan->mbox->num_chans) {
		dev_err(chan->mbox->dev,
			"invalid master ID %u for HSP channel\n",
			db->master);
		return -EINVAL;
	}

	ccplex = tegra_hsp_doorbell_get(hsp, TEGRA_HSP_DB_MASTER_CCPLEX);
	if (!ccplex)
		return -ENODEV;

	if (!tegra_hsp_doorbell_can_ring(db))
		return -ENODEV;

	spin_lock_irqsave(&hsp->lock, flags);

	value = tegra_hsp_channel_readl(&ccplex->channel, HSP_DB_ENABLE);
	value |= BIT(db->master);
	tegra_hsp_channel_writel(&ccplex->channel, value, HSP_DB_ENABLE);

	spin_unlock_irqrestore(&hsp->lock, flags);

	return 0;
}