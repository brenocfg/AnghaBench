#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct TYPE_5__ {TYPE_1__* dev; } ;
struct TYPE_6__ {struct atmel_hlcdc_layer_desc* desc; } ;
struct atmel_hlcdc_plane {TYPE_2__ base; TYPE_3__ layer; } ;
struct atmel_hlcdc_layer_desc {int /*<<< orphan*/  name; } ;
struct TYPE_4__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  ATMEL_HLCDC_LAYER_ISR ; 
 int ATMEL_HLCDC_LAYER_OVR_IRQ (int) ; 
 int atmel_hlcdc_layer_read_reg (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 

void atmel_hlcdc_plane_irq(struct atmel_hlcdc_plane *plane)
{
	const struct atmel_hlcdc_layer_desc *desc = plane->layer.desc;
	u32 isr;

	isr = atmel_hlcdc_layer_read_reg(&plane->layer, ATMEL_HLCDC_LAYER_ISR);

	/*
	 * There's not much we can do in case of overrun except informing
	 * the user. However, we are in interrupt context here, hence the
	 * use of dev_dbg().
	 */
	if (isr &
	    (ATMEL_HLCDC_LAYER_OVR_IRQ(0) | ATMEL_HLCDC_LAYER_OVR_IRQ(1) |
	     ATMEL_HLCDC_LAYER_OVR_IRQ(2)))
		dev_dbg(plane->base.dev->dev, "overrun on plane %s\n",
			desc->name);
}