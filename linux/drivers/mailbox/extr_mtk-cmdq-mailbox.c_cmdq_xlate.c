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
struct mbox_chan {scalar_t__ con_priv; } ;
struct cmdq_thread {int priority; int atomic_exec; struct mbox_chan* chan; } ;

/* Variables and functions */
 int /*<<< orphan*/  EINVAL ; 
 struct mbox_chan* ERR_PTR (int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct mbox_chan *cmdq_xlate(struct mbox_controller *mbox,
		const struct of_phandle_args *sp)
{
	int ind = sp->args[0];
	struct cmdq_thread *thread;

	if (ind >= mbox->num_chans)
		return ERR_PTR(-EINVAL);

	thread = (struct cmdq_thread *)mbox->chans[ind].con_priv;
	thread->priority = sp->args[1];
	thread->atomic_exec = (sp->args[2] != 0);
	thread->chan = &mbox->chans[ind];

	return &mbox->chans[ind];
}