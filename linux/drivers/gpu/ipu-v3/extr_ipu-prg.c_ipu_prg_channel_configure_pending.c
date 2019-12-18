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
struct ipuv3_channel {TYPE_1__* ipu; int /*<<< orphan*/  num; } ;
struct ipu_prg_channel {size_t used_pre; int /*<<< orphan*/  enabled; } ;
struct ipu_prg {int /*<<< orphan*/ * pres; struct ipu_prg_channel* chan; } ;
struct TYPE_2__ {struct ipu_prg* prg_priv; } ;

/* Variables and functions */
 int /*<<< orphan*/  WARN_ON (int) ; 
 int ipu_pre_update_pending (int /*<<< orphan*/ ) ; 
 int ipu_prg_ipu_to_prg_chan (int /*<<< orphan*/ ) ; 

bool ipu_prg_channel_configure_pending(struct ipuv3_channel *ipu_chan)
{
	int prg_chan = ipu_prg_ipu_to_prg_chan(ipu_chan->num);
	struct ipu_prg *prg = ipu_chan->ipu->prg_priv;
	struct ipu_prg_channel *chan;

	if (prg_chan < 0)
		return false;

	chan = &prg->chan[prg_chan];
	WARN_ON(!chan->enabled);

	return ipu_pre_update_pending(prg->pres[chan->used_pre]);
}