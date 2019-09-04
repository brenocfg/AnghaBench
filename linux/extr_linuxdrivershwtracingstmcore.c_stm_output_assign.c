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
struct stp_policy_node {int dummy; } ;
struct stm_output {unsigned int nr_chans; unsigned int master; unsigned int channel; int /*<<< orphan*/  lock; } ;
struct stm_device {int /*<<< orphan*/  mc_lock; int /*<<< orphan*/  dev; TYPE_1__* data; } ;
struct TYPE_2__ {unsigned int sw_nchannels; unsigned int sw_start; unsigned int sw_end; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ WARN_ON_ONCE (unsigned int) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,unsigned int,unsigned int,unsigned int) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int stm_find_master_chan (struct stm_device*,unsigned int,unsigned int*,unsigned int,unsigned int*,unsigned int) ; 
 int /*<<< orphan*/  stm_output_claim (struct stm_device*,struct stm_output*) ; 
 int /*<<< orphan*/  stp_policy_node_get_ranges (struct stp_policy_node*,unsigned int*,unsigned int*,unsigned int*,unsigned int*) ; 

__attribute__((used)) static int stm_output_assign(struct stm_device *stm, unsigned int width,
			     struct stp_policy_node *policy_node,
			     struct stm_output *output)
{
	unsigned int midx, cidx, mend, cend;
	int ret = -EINVAL;

	if (width > stm->data->sw_nchannels)
		return -EINVAL;

	if (policy_node) {
		stp_policy_node_get_ranges(policy_node,
					   &midx, &mend, &cidx, &cend);
	} else {
		midx = stm->data->sw_start;
		cidx = 0;
		mend = stm->data->sw_end;
		cend = stm->data->sw_nchannels - 1;
	}

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
	stm_output_claim(stm, output);
	dev_dbg(&stm->dev, "assigned %u:%u (+%u)\n", midx, cidx, width);

	ret = 0;
unlock:
	spin_unlock(&output->lock);
	spin_unlock(&stm->mc_lock);

	return ret;
}