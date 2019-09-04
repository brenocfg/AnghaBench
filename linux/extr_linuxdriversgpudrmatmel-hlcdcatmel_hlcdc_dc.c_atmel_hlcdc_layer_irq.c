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
struct atmel_hlcdc_layer {TYPE_1__* desc; } ;
struct TYPE_2__ {scalar_t__ type; } ;

/* Variables and functions */
 scalar_t__ ATMEL_HLCDC_BASE_LAYER ; 
 scalar_t__ ATMEL_HLCDC_CURSOR_LAYER ; 
 scalar_t__ ATMEL_HLCDC_OVERLAY_LAYER ; 
 int /*<<< orphan*/  atmel_hlcdc_layer_to_plane (struct atmel_hlcdc_layer*) ; 
 int /*<<< orphan*/  atmel_hlcdc_plane_irq (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void atmel_hlcdc_layer_irq(struct atmel_hlcdc_layer *layer)
{
	if (!layer)
		return;

	if (layer->desc->type == ATMEL_HLCDC_BASE_LAYER ||
	    layer->desc->type == ATMEL_HLCDC_OVERLAY_LAYER ||
	    layer->desc->type == ATMEL_HLCDC_CURSOR_LAYER)
		atmel_hlcdc_plane_irq(atmel_hlcdc_layer_to_plane(layer));
}