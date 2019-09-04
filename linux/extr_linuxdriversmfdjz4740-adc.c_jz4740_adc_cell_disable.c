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
struct TYPE_2__ {int /*<<< orphan*/  parent; } ;
struct platform_device {int /*<<< orphan*/  id; TYPE_1__ dev; } ;
struct jz4740_adc {int dummy; } ;

/* Variables and functions */
 struct jz4740_adc* dev_get_drvdata (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jz4740_adc_clk_disable (struct jz4740_adc*) ; 
 int /*<<< orphan*/  jz4740_adc_set_enabled (struct jz4740_adc*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int jz4740_adc_cell_disable(struct platform_device *pdev)
{
	struct jz4740_adc *adc = dev_get_drvdata(pdev->dev.parent);

	jz4740_adc_set_enabled(adc, pdev->id, false);
	jz4740_adc_clk_disable(adc);

	return 0;
}