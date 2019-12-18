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
struct mbox_controller {struct mbox_chan* chans; struct device* dev; } ;
struct mbox_chan {int dummy; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  EINVAL ; 
 struct mbox_chan* ERR_PTR (int /*<<< orphan*/ ) ; 
 unsigned int IPI_MB_CHNL_RX ; 
 unsigned int IPI_MB_CHNL_TX ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,unsigned int) ; 

__attribute__((used)) static struct mbox_chan *zynqmp_ipi_of_xlate(struct mbox_controller *mbox,
					     const struct of_phandle_args *p)
{
	struct mbox_chan *chan;
	struct device *dev = mbox->dev;
	unsigned int chan_type;

	/* Only supports TX and RX channels */
	chan_type = p->args[0];
	if (chan_type != IPI_MB_CHNL_TX && chan_type != IPI_MB_CHNL_RX) {
		dev_err(dev, "req chnl failure: invalid chnl type %u.\n",
			chan_type);
		return ERR_PTR(-EINVAL);
	}
	chan = &mbox->chans[chan_type];
	return chan;
}