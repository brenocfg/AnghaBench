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
struct dsp_pipeline {int /*<<< orphan*/  list; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 

int dsp_pipeline_init(struct dsp_pipeline *pipeline)
{
	if (!pipeline)
		return -EINVAL;

	INIT_LIST_HEAD(&pipeline->list);

#ifdef PIPELINE_DEBUG
	printk(KERN_DEBUG "%s: dsp pipeline ready\n", __func__);
#endif

	return 0;
}