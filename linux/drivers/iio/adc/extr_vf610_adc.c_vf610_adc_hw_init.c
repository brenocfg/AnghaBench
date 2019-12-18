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
struct vf610_adc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  vf610_adc_calibration (struct vf610_adc*) ; 
 int /*<<< orphan*/  vf610_adc_cfg_post_set (struct vf610_adc*) ; 
 int /*<<< orphan*/  vf610_adc_cfg_set (struct vf610_adc*) ; 
 int /*<<< orphan*/  vf610_adc_sample_set (struct vf610_adc*) ; 

__attribute__((used)) static void vf610_adc_hw_init(struct vf610_adc *info)
{
	/* CFG: Feature set */
	vf610_adc_cfg_post_set(info);
	vf610_adc_sample_set(info);

	/* adc calibration */
	vf610_adc_calibration(info);

	/* CFG: power and speed set */
	vf610_adc_cfg_set(info);
}