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
typedef  int u32 ;
struct stm32_spi {scalar_t__ cur_midi; int cur_speed; scalar_t__ base; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int DIV_ROUND_UP (scalar_t__,int) ; 
 scalar_t__ SPI_1HZ_NS ; 
 scalar_t__ STM32H7_SPI_CFG2 ; 
 int STM32H7_SPI_CFG2_MIDI ; 
 int STM32H7_SPI_CFG2_MIDI_SHIFT ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int,int,int) ; 
 int min (int,int) ; 
 int readl_relaxed (scalar_t__) ; 
 int /*<<< orphan*/  writel_relaxed (int,scalar_t__) ; 

__attribute__((used)) static void stm32h7_spi_data_idleness(struct stm32_spi *spi, u32 len)
{
	u32 cfg2_clrb = 0, cfg2_setb = 0;

	cfg2_clrb |= STM32H7_SPI_CFG2_MIDI;
	if ((len > 1) && (spi->cur_midi > 0)) {
		u32 sck_period_ns = DIV_ROUND_UP(SPI_1HZ_NS, spi->cur_speed);
		u32 midi = min((u32)DIV_ROUND_UP(spi->cur_midi, sck_period_ns),
			       (u32)STM32H7_SPI_CFG2_MIDI >>
			       STM32H7_SPI_CFG2_MIDI_SHIFT);

		dev_dbg(spi->dev, "period=%dns, midi=%d(=%dns)\n",
			sck_period_ns, midi, midi * sck_period_ns);
		cfg2_setb |= (midi << STM32H7_SPI_CFG2_MIDI_SHIFT) &
			     STM32H7_SPI_CFG2_MIDI;
	}

	writel_relaxed((readl_relaxed(spi->base + STM32H7_SPI_CFG2) &
			~cfg2_clrb) | cfg2_setb,
		       spi->base + STM32H7_SPI_CFG2);
}