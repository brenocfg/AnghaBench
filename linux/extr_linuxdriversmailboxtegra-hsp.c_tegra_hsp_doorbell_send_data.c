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
struct tegra_hsp_doorbell {int /*<<< orphan*/  channel; } ;
struct mbox_chan {struct tegra_hsp_doorbell* con_priv; } ;

/* Variables and functions */
 int /*<<< orphan*/  HSP_DB_TRIGGER ; 
 int /*<<< orphan*/  tegra_hsp_channel_writel (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int tegra_hsp_doorbell_send_data(struct mbox_chan *chan, void *data)
{
	struct tegra_hsp_doorbell *db = chan->con_priv;

	tegra_hsp_channel_writel(&db->channel, 1, HSP_DB_TRIGGER);

	return 0;
}