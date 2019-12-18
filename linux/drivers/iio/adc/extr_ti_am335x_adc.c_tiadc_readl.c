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
struct tiadc_device {TYPE_1__* mfd_tscadc; } ;
struct TYPE_2__ {scalar_t__ tscadc_base; } ;

/* Variables and functions */
 unsigned int readl (scalar_t__) ; 

__attribute__((used)) static unsigned int tiadc_readl(struct tiadc_device *adc, unsigned int reg)
{
	return readl(adc->mfd_tscadc->tscadc_base + reg);
}