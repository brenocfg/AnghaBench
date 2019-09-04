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
struct stm_output {int /*<<< orphan*/  lock; scalar_t__ nr_chans; } ;
struct stm_device {int /*<<< orphan*/  mc_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stm_output_disclaim (struct stm_device*,struct stm_output*) ; 

__attribute__((used)) static void stm_output_free(struct stm_device *stm, struct stm_output *output)
{
	spin_lock(&stm->mc_lock);
	spin_lock(&output->lock);
	if (output->nr_chans)
		stm_output_disclaim(stm, output);
	spin_unlock(&output->lock);
	spin_unlock(&stm->mc_lock);
}