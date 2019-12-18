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
struct of_phandle_args {unsigned int* args; } ;
struct mbox_controller {int dummy; } ;
struct mbox_chan {int dummy; } ;
struct hi3660_mbox {struct mbox_chan* chan; struct hi3660_chan_info* mchan; int /*<<< orphan*/  dev; } ;
struct hi3660_chan_info {unsigned int dst_irq; unsigned int ack_irq; } ;

/* Variables and functions */
 int /*<<< orphan*/  EINVAL ; 
 struct mbox_chan* ERR_PTR (int /*<<< orphan*/ ) ; 
 unsigned int MBOX_CHAN_MAX ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,unsigned int) ; 
 struct hi3660_mbox* to_hi3660_mbox (struct mbox_controller*) ; 

__attribute__((used)) static struct mbox_chan *hi3660_mbox_xlate(struct mbox_controller *controller,
					   const struct of_phandle_args *spec)
{
	struct hi3660_mbox *mbox = to_hi3660_mbox(controller);
	struct hi3660_chan_info *mchan;
	unsigned int ch = spec->args[0];

	if (ch >= MBOX_CHAN_MAX) {
		dev_err(mbox->dev, "Invalid channel idx %d\n", ch);
		return ERR_PTR(-EINVAL);
	}

	mchan = &mbox->mchan[ch];
	mchan->dst_irq = spec->args[1];
	mchan->ack_irq = spec->args[2];

	return &mbox->chan[ch];
}