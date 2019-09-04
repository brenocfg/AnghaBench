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
struct stp_master {scalar_t__ nr_free; int /*<<< orphan*/ * chan_map; } ;
struct stm_output {scalar_t__ nr_chans; int /*<<< orphan*/  channel; int /*<<< orphan*/  lock; int /*<<< orphan*/  master; } ;
struct stm_device {int /*<<< orphan*/  mc_lock; } ;

/* Variables and functions */
 scalar_t__ WARN_ON_ONCE (int) ; 
 int /*<<< orphan*/  bitmap_allocate_region (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ilog2 (scalar_t__) ; 
 int /*<<< orphan*/  lockdep_assert_held (int /*<<< orphan*/ *) ; 
 struct stp_master* stm_master (struct stm_device*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void stm_output_claim(struct stm_device *stm, struct stm_output *output)
{
	struct stp_master *master = stm_master(stm, output->master);

	lockdep_assert_held(&stm->mc_lock);
	lockdep_assert_held(&output->lock);

	if (WARN_ON_ONCE(master->nr_free < output->nr_chans))
		return;

	bitmap_allocate_region(&master->chan_map[0], output->channel,
			       ilog2(output->nr_chans));

	master->nr_free -= output->nr_chans;
}