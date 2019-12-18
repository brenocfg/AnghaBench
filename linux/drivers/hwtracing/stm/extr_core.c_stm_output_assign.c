#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct stp_policy_node {int dummy; } ;
struct stm_output {int nr_chans; unsigned int master; unsigned int channel; int /*<<< orphan*/  lock; } ;
struct stm_device {int /*<<< orphan*/  mc_lock; int /*<<< orphan*/  dev; TYPE_2__* pdrv; TYPE_1__* data; } ;
struct TYPE_4__ {int (* output_open ) (void*,struct stm_output*) ;} ;
struct TYPE_3__ {unsigned int sw_nchannels; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ WARN_ON_ONCE (int) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,unsigned int,unsigned int,unsigned int) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int stm_find_master_chan (struct stm_device*,unsigned int,unsigned int*,unsigned int,unsigned int*,unsigned int) ; 
 int /*<<< orphan*/  stm_output_claim (struct stm_device*,struct stm_output*) ; 
 int /*<<< orphan*/  stp_policy_node_get_ranges (struct stp_policy_node*,unsigned int*,unsigned int*,unsigned int*,unsigned int*) ; 
 void* stp_policy_node_priv (struct stp_policy_node*) ; 
 int stub1 (void*,struct stm_output*) ; 

__attribute__((used)) static int stm_output_assign(struct stm_device *stm, unsigned int width,
			     struct stp_policy_node *policy_node,
			     struct stm_output *output)
{
	unsigned int midx, cidx, mend, cend;
	int ret = -EINVAL;

	if (width > stm->data->sw_nchannels)
		return -EINVAL;

	/* We no longer accept policy_node==NULL here */
	if (WARN_ON_ONCE(!policy_node))
		return -EINVAL;

	/*
	 * Also, the caller holds reference to policy_node, so it won't
	 * disappear on us.
	 */
	stp_policy_node_get_ranges(policy_node, &midx, &mend, &cidx, &cend);

	spin_lock(&stm->mc_lock);
	spin_lock(&output->lock);
	/* output is already assigned -- shouldn't happen */
	if (WARN_ON_ONCE(output->nr_chans))
		goto unlock;

	ret = stm_find_master_chan(stm, width, &midx, mend, &cidx, cend);
	if (ret < 0)
		goto unlock;

	output->master = midx;
	output->channel = cidx;
	output->nr_chans = width;
	if (stm->pdrv->output_open) {
		void *priv = stp_policy_node_priv(policy_node);

		if (WARN_ON_ONCE(!priv))
			goto unlock;

		/* configfs subsys mutex is held by the caller */
		ret = stm->pdrv->output_open(priv, output);
		if (ret)
			goto unlock;
	}

	stm_output_claim(stm, output);
	dev_dbg(&stm->dev, "assigned %u:%u (+%u)\n", midx, cidx, width);

	ret = 0;
unlock:
	if (ret)
		output->nr_chans = 0;

	spin_unlock(&output->lock);
	spin_unlock(&stm->mc_lock);

	return ret;
}