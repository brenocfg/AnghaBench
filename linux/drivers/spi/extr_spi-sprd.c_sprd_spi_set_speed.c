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
struct sprd_spi {int src_clk; int hw_speed_hz; scalar_t__ base; } ;

/* Variables and functions */
 int DIV_ROUND_UP (int,int) ; 
 scalar_t__ SPRD_SPI_CLKD ; 
 int /*<<< orphan*/  writel_relaxed (int,scalar_t__) ; 

__attribute__((used)) static void sprd_spi_set_speed(struct sprd_spi *ss, u32 speed_hz)
{
	/*
	 * From SPI datasheet, the prescale calculation formula:
	 * prescale = SPI source clock / (2 * SPI_freq) - 1;
	 */
	u32 clk_div = DIV_ROUND_UP(ss->src_clk, speed_hz << 1) - 1;

	/* Save the real hardware speed */
	ss->hw_speed_hz = (ss->src_clk >> 1) / (clk_div + 1);
	writel_relaxed(clk_div, ss->base + SPRD_SPI_CLKD);
}