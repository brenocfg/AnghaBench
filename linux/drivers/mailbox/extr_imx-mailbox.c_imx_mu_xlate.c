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
typedef  int u32 ;
struct of_phandle_args {int args_count; int* args; } ;
struct mbox_controller {int num_chans; struct mbox_chan* chans; int /*<<< orphan*/  dev; } ;
struct mbox_chan {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  EINVAL ; 
 struct mbox_chan* ERR_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int,...) ; 

__attribute__((used)) static struct mbox_chan * imx_mu_xlate(struct mbox_controller *mbox,
				       const struct of_phandle_args *sp)
{
	u32 type, idx, chan;

	if (sp->args_count != 2) {
		dev_err(mbox->dev, "Invalid argument count %d\n", sp->args_count);
		return ERR_PTR(-EINVAL);
	}

	type = sp->args[0]; /* channel type */
	idx = sp->args[1]; /* index */
	chan = type * 4 + idx;

	if (chan >= mbox->num_chans) {
		dev_err(mbox->dev, "Not supported channel number: %d. (type: %d, idx: %d)\n", chan, type, idx);
		return ERR_PTR(-EINVAL);
	}

	return &mbox->chans[chan];
}