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
typedef  int u8 ;
struct sii8620 {int dummy; } ;

/* Variables and functions */
 int BIT_EMSCINTR_SPI_DVLD ; 
 int BIT_SPIBURSTSTAT_EMSC_NORMAL_MODE ; 
 int /*<<< orphan*/  REG_EMSCINTR ; 
 int /*<<< orphan*/  REG_SPIBURSTSTAT ; 
 int /*<<< orphan*/  sii8620_burst_receive (struct sii8620*) ; 
 int sii8620_readb (struct sii8620*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sii8620_write (struct sii8620*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void sii8620_irq_block(struct sii8620 *ctx)
{
	u8 stat = sii8620_readb(ctx, REG_EMSCINTR);

	if (stat & BIT_EMSCINTR_SPI_DVLD) {
		u8 bstat = sii8620_readb(ctx, REG_SPIBURSTSTAT);

		if (bstat & BIT_SPIBURSTSTAT_EMSC_NORMAL_MODE)
			sii8620_burst_receive(ctx);
	}

	sii8620_write(ctx, REG_EMSCINTR, stat);
}