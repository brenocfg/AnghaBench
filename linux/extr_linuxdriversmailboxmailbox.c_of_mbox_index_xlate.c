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
struct of_phandle_args {int* args; } ;
struct mbox_controller {int num_chans; struct mbox_chan* chans; } ;
struct mbox_chan {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  EINVAL ; 
 struct mbox_chan* ERR_PTR (int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct mbox_chan *
of_mbox_index_xlate(struct mbox_controller *mbox,
		    const struct of_phandle_args *sp)
{
	int ind = sp->args[0];

	if (ind >= mbox->num_chans)
		return ERR_PTR(-EINVAL);

	return &mbox->chans[ind];
}