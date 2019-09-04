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
typedef  int uint32_t ;
struct TYPE_2__ {int raw_size; int banks_num; int dram_channels_num; } ;
struct dce112_compressor {TYPE_1__ base; } ;

/* Variables and functions */

__attribute__((used)) static uint32_t lpt_size_alignment(struct dce112_compressor *cp110)
{
	/*LPT_ALIGNMENT (in bytes) = ROW_SIZE * #BANKS * # DRAM CHANNELS. */
	return cp110->base.raw_size * cp110->base.banks_num *
		cp110->base.dram_channels_num;
}