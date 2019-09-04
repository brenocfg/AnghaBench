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
struct drm_device {struct atmel_hlcdc_dc* dev_private; } ;
struct atmel_hlcdc_dc {int /*<<< orphan*/ * layers; int /*<<< orphan*/  crtc; TYPE_1__* hlcdc; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;
struct TYPE_2__ {int /*<<< orphan*/  regmap; } ;

/* Variables and functions */
 int /*<<< orphan*/  ATMEL_HLCDC_IMR ; 
 int /*<<< orphan*/  ATMEL_HLCDC_ISR ; 
 unsigned long ATMEL_HLCDC_LAYER_STATUS (int) ; 
 int ATMEL_HLCDC_MAX_LAYERS ; 
 unsigned long ATMEL_HLCDC_SOF ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  IRQ_NONE ; 
 int /*<<< orphan*/  atmel_hlcdc_crtc_irq (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  atmel_hlcdc_layer_irq (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  regmap_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int*) ; 

__attribute__((used)) static irqreturn_t atmel_hlcdc_dc_irq_handler(int irq, void *data)
{
	struct drm_device *dev = data;
	struct atmel_hlcdc_dc *dc = dev->dev_private;
	unsigned long status;
	unsigned int imr, isr;
	int i;

	regmap_read(dc->hlcdc->regmap, ATMEL_HLCDC_IMR, &imr);
	regmap_read(dc->hlcdc->regmap, ATMEL_HLCDC_ISR, &isr);
	status = imr & isr;
	if (!status)
		return IRQ_NONE;

	if (status & ATMEL_HLCDC_SOF)
		atmel_hlcdc_crtc_irq(dc->crtc);

	for (i = 0; i < ATMEL_HLCDC_MAX_LAYERS; i++) {
		if (ATMEL_HLCDC_LAYER_STATUS(i) & status)
			atmel_hlcdc_layer_irq(dc->layers[i]);
	}

	return IRQ_HANDLED;
}