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
struct of_phandle_args {int args_count; size_t* args; } ;
struct mbox_controller {size_t num_chans; struct mbox_chan* chans; } ;
struct mbox_chan {struct flexrm_ring* con_priv; } ;
struct flexrm_ring {size_t msi_count_threshold; size_t msi_timer_val; } ;

/* Variables and functions */
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  ENOENT ; 
 struct mbox_chan* ERR_PTR (int /*<<< orphan*/ ) ; 
 size_t MSI_COUNT_MASK ; 
 size_t MSI_TIMER_VAL_MASK ; 

__attribute__((used)) static struct mbox_chan *flexrm_mbox_of_xlate(struct mbox_controller *cntlr,
					const struct of_phandle_args *pa)
{
	struct mbox_chan *chan;
	struct flexrm_ring *ring;

	if (pa->args_count < 3)
		return ERR_PTR(-EINVAL);

	if (pa->args[0] >= cntlr->num_chans)
		return ERR_PTR(-ENOENT);

	if (pa->args[1] > MSI_COUNT_MASK)
		return ERR_PTR(-EINVAL);

	if (pa->args[2] > MSI_TIMER_VAL_MASK)
		return ERR_PTR(-EINVAL);

	chan = &cntlr->chans[pa->args[0]];
	ring = chan->con_priv;
	ring->msi_count_threshold = pa->args[1];
	ring->msi_timer_val = pa->args[2];

	return chan;
}