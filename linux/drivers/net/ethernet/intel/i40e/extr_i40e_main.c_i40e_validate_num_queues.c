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
struct i40e_vsi {int current_rss_size; } ;
struct i40e_pf {TYPE_1__* pdev; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,int,int) ; 
 int i40e_get_max_queues_for_channel (struct i40e_vsi*) ; 
 int /*<<< orphan*/  is_power_of_2 (int) ; 

__attribute__((used)) static int i40e_validate_num_queues(struct i40e_pf *pf, int num_queues,
				    struct i40e_vsi *vsi, bool *reconfig_rss)
{
	int max_ch_queues;

	if (!reconfig_rss)
		return -EINVAL;

	*reconfig_rss = false;
	if (vsi->current_rss_size) {
		if (num_queues > vsi->current_rss_size) {
			dev_dbg(&pf->pdev->dev,
				"Error: num_queues (%d) > vsi's current_size(%d)\n",
				num_queues, vsi->current_rss_size);
			return -EINVAL;
		} else if ((num_queues < vsi->current_rss_size) &&
			   (!is_power_of_2(num_queues))) {
			dev_dbg(&pf->pdev->dev,
				"Error: num_queues (%d) < vsi's current_size(%d), but not power of 2\n",
				num_queues, vsi->current_rss_size);
			return -EINVAL;
		}
	}

	if (!is_power_of_2(num_queues)) {
		/* Find the max num_queues configured for channel if channel
		 * exist.
		 * if channel exist, then enforce 'num_queues' to be more than
		 * max ever queues configured for channel.
		 */
		max_ch_queues = i40e_get_max_queues_for_channel(vsi);
		if (num_queues < max_ch_queues) {
			dev_dbg(&pf->pdev->dev,
				"Error: num_queues (%d) < max queues configured for channel(%d)\n",
				num_queues, max_ch_queues);
			return -EINVAL;
		}
		*reconfig_rss = true;
	}

	return 0;
}