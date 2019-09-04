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

/* Variables and functions */
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  THIS_MODULE ; 
 int /*<<< orphan*/  class_create (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  dsp_hwec_init () ; 
 int /*<<< orphan*/  elements_class ; 

int dsp_pipeline_module_init(void)
{
	elements_class = class_create(THIS_MODULE, "dsp_pipeline");
	if (IS_ERR(elements_class))
		return PTR_ERR(elements_class);

#ifdef PIPELINE_DEBUG
	printk(KERN_DEBUG "%s: dsp pipeline module initialized\n", __func__);
#endif

	dsp_hwec_init();

	return 0;
}