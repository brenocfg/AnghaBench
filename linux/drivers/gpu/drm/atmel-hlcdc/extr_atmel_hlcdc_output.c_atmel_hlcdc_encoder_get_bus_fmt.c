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
struct drm_encoder {int dummy; } ;
struct atmel_hlcdc_rgb_output {int bus_fmt; } ;

/* Variables and functions */
 struct atmel_hlcdc_rgb_output* atmel_hlcdc_encoder_to_rgb_output (struct drm_encoder*) ; 

int atmel_hlcdc_encoder_get_bus_fmt(struct drm_encoder *encoder)
{
	struct atmel_hlcdc_rgb_output *output;

	output = atmel_hlcdc_encoder_to_rgb_output(encoder);

	return output->bus_fmt;
}