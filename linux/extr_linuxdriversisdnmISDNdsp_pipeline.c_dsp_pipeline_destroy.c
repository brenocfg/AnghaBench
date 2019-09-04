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
struct dsp_pipeline {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  _dsp_pipeline_destroy (struct dsp_pipeline*) ; 

void dsp_pipeline_destroy(struct dsp_pipeline *pipeline)
{

	if (!pipeline)
		return;

	_dsp_pipeline_destroy(pipeline);

#ifdef PIPELINE_DEBUG
	printk(KERN_DEBUG "%s: dsp pipeline destroyed\n", __func__);
#endif
}