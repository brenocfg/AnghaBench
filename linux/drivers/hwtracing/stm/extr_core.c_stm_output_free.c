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
struct stm_output {int /*<<< orphan*/  lock; scalar_t__ nr_chans; } ;
struct stm_device {int /*<<< orphan*/  mc_lock; TYPE_1__* pdrv; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* output_close ) (struct stm_output*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stm_output_disclaim (struct stm_device*,struct stm_output*) ; 
 int /*<<< orphan*/  stub1 (struct stm_output*) ; 

__attribute__((used)) static void stm_output_free(struct stm_device *stm, struct stm_output *output)
{
	spin_lock(&stm->mc_lock);
	spin_lock(&output->lock);
	if (output->nr_chans)
		stm_output_disclaim(stm, output);
	if (stm->pdrv && stm->pdrv->output_close)
		stm->pdrv->output_close(output);
	spin_unlock(&output->lock);
	spin_unlock(&stm->mc_lock);
}