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
struct isp_pipeline {int l3_ick; } ;
struct TYPE_2__ {int /*<<< orphan*/  entity; } ;
struct isp_ccdc_device {scalar_t__ input; TYPE_1__ subdev; } ;

/* Variables and functions */
 scalar_t__ CCDC_INPUT_PARALLEL ; 
 unsigned int min (unsigned int,unsigned int) ; 
 struct isp_pipeline* to_isp_pipeline (int /*<<< orphan*/ *) ; 

void omap3isp_ccdc_max_rate(struct isp_ccdc_device *ccdc,
			    unsigned int *max_rate)
{
	struct isp_pipeline *pipe = to_isp_pipeline(&ccdc->subdev.entity);
	unsigned int rate;

	if (pipe == NULL)
		return;

	/*
	 * TRM says that for parallel sensors the maximum data rate
	 * should be 90% form L3/2 clock, otherwise just L3/2.
	 */
	if (ccdc->input == CCDC_INPUT_PARALLEL)
		rate = pipe->l3_ick / 2 * 9 / 10;
	else
		rate = pipe->l3_ick / 2;

	*max_rate = min(*max_rate, rate);
}