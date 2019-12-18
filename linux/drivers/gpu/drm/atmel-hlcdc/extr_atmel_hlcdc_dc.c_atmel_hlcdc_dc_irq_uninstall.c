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
struct atmel_hlcdc_dc {TYPE_1__* hlcdc; } ;
struct TYPE_2__ {int /*<<< orphan*/  regmap; } ;

/* Variables and functions */
 int /*<<< orphan*/  ATMEL_HLCDC_IDR ; 
 int /*<<< orphan*/  ATMEL_HLCDC_ISR ; 
 int /*<<< orphan*/  regmap_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int*) ; 
 int /*<<< orphan*/  regmap_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void atmel_hlcdc_dc_irq_uninstall(struct drm_device *dev)
{
	struct atmel_hlcdc_dc *dc = dev->dev_private;
	unsigned int isr;

	regmap_write(dc->hlcdc->regmap, ATMEL_HLCDC_IDR, 0xffffffff);
	regmap_read(dc->hlcdc->regmap, ATMEL_HLCDC_ISR, &isr);
}