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
struct tegra_hsp_channel {struct tegra_hsp_channel* chan; struct tegra_hsp_channel* con_priv; } ;
struct tegra_hsp_doorbell {struct tegra_hsp_channel channel; } ;
struct TYPE_2__ {unsigned int num_chans; struct tegra_hsp_channel* chans; } ;
struct tegra_hsp {int /*<<< orphan*/  lock; TYPE_1__ mbox; } ;
struct of_phandle_args {unsigned int* args; } ;
struct mbox_controller {int dummy; } ;
struct mbox_chan {struct mbox_chan* chan; struct mbox_chan* con_priv; } ;

/* Variables and functions */
 int /*<<< orphan*/  EBUSY ; 
 int /*<<< orphan*/  ENODEV ; 
 struct tegra_hsp_channel* ERR_CAST (struct tegra_hsp_channel*) ; 
 struct tegra_hsp_channel* ERR_PTR (int /*<<< orphan*/ ) ; 
 scalar_t__ IS_ERR (struct tegra_hsp_channel*) ; 
#define  TEGRA_HSP_MBOX_TYPE_DB 128 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 struct tegra_hsp_doorbell* tegra_hsp_doorbell_get (struct tegra_hsp*,unsigned int) ; 
 struct tegra_hsp* to_tegra_hsp (struct mbox_controller*) ; 

__attribute__((used)) static struct mbox_chan *of_tegra_hsp_xlate(struct mbox_controller *mbox,
					    const struct of_phandle_args *args)
{
	struct tegra_hsp_channel *channel = ERR_PTR(-ENODEV);
	struct tegra_hsp *hsp = to_tegra_hsp(mbox);
	unsigned int type = args->args[0];
	unsigned int master = args->args[1];
	struct tegra_hsp_doorbell *db;
	struct mbox_chan *chan;
	unsigned long flags;
	unsigned int i;

	switch (type) {
	case TEGRA_HSP_MBOX_TYPE_DB:
		db = tegra_hsp_doorbell_get(hsp, master);
		if (db)
			channel = &db->channel;

		break;

	default:
		break;
	}

	if (IS_ERR(channel))
		return ERR_CAST(channel);

	spin_lock_irqsave(&hsp->lock, flags);

	for (i = 0; i < hsp->mbox.num_chans; i++) {
		chan = &hsp->mbox.chans[i];
		if (!chan->con_priv) {
			chan->con_priv = channel;
			channel->chan = chan;
			break;
		}

		chan = NULL;
	}

	spin_unlock_irqrestore(&hsp->lock, flags);

	return chan ?: ERR_PTR(-EBUSY);
}