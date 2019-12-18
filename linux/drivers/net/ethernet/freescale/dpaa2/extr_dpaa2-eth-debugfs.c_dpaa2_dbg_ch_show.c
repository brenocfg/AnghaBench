#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct seq_file {scalar_t__ private; } ;
struct dpaa2_eth_priv {int num_channels; struct dpaa2_eth_channel** channel; TYPE_1__* net_dev; } ;
struct TYPE_6__ {char* dequeue_portal_busy; char* cdan; } ;
struct TYPE_5__ {char* desired_cpu; } ;
struct dpaa2_eth_channel {char* ch_id; char* buf_count; TYPE_3__ stats; TYPE_2__ nctx; } ;
struct TYPE_4__ {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  seq_printf (struct seq_file*,char*,char*,...) ; 

__attribute__((used)) static int dpaa2_dbg_ch_show(struct seq_file *file, void *offset)
{
	struct dpaa2_eth_priv *priv = (struct dpaa2_eth_priv *)file->private;
	struct dpaa2_eth_channel *ch;
	int i;

	seq_printf(file, "Channel stats for %s:\n", priv->net_dev->name);
	seq_printf(file, "%s%16s%16s%16s%16s\n",
		   "CHID", "CPU", "Deq busy", "CDANs", "Buf count");

	for (i = 0; i < priv->num_channels; i++) {
		ch = priv->channel[i];
		seq_printf(file, "%4d%16d%16llu%16llu%16d\n",
			   ch->ch_id,
			   ch->nctx.desired_cpu,
			   ch->stats.dequeue_portal_busy,
			   ch->stats.cdan,
			   ch->buf_count);
	}

	return 0;
}