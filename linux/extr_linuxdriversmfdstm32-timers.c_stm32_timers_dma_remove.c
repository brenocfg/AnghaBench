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
struct TYPE_2__ {scalar_t__* chans; } ;
struct stm32_timers {TYPE_1__ dma; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int STM32_TIMERS_DMA_CH1 ; 
 int STM32_TIMERS_MAX_DMAS ; 
 int /*<<< orphan*/  dma_release_channel (scalar_t__) ; 

__attribute__((used)) static void stm32_timers_dma_remove(struct device *dev,
				    struct stm32_timers *ddata)
{
	int i;

	for (i = STM32_TIMERS_DMA_CH1; i < STM32_TIMERS_MAX_DMAS; i++)
		if (ddata->dma.chans[i])
			dma_release_channel(ddata->dma.chans[i]);
}