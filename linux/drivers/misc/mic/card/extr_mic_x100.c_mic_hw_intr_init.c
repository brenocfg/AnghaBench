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
struct TYPE_2__ {scalar_t__ num_intr; } ;
struct mic_driver {TYPE_1__ intr_info; } ;

/* Variables and functions */
 scalar_t__ MIC_X100_NUM_RDMASR_IRQ ; 
 scalar_t__ MIC_X100_NUM_SBOX_IRQ ; 

void mic_hw_intr_init(struct mic_driver *mdrv)
{
	mdrv->intr_info.num_intr = MIC_X100_NUM_SBOX_IRQ +
				MIC_X100_NUM_RDMASR_IRQ;
}