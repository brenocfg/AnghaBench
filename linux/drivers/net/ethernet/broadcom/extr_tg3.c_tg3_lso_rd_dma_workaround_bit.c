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
typedef  int /*<<< orphan*/  u32 ;
struct tg3 {int dummy; } ;

/* Variables and functions */
 scalar_t__ ASIC_REV_5719 ; 
 int /*<<< orphan*/  TG3_LSO_RD_DMA_TX_LENGTH_WA_5719 ; 
 int /*<<< orphan*/  TG3_LSO_RD_DMA_TX_LENGTH_WA_5720 ; 
 scalar_t__ tg3_asic_rev (struct tg3*) ; 

__attribute__((used)) static inline u32 tg3_lso_rd_dma_workaround_bit(struct tg3 *tp)
{
	if (tg3_asic_rev(tp) == ASIC_REV_5719)
		return TG3_LSO_RD_DMA_TX_LENGTH_WA_5719;
	else
		return TG3_LSO_RD_DMA_TX_LENGTH_WA_5720;
}