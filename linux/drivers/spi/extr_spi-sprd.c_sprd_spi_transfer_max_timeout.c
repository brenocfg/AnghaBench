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
struct sprd_spi {int word_delay; int /*<<< orphan*/  src_clk; int /*<<< orphan*/  hw_speed_hz; } ;
struct spi_transfer {int bits_per_word; } ;

/* Variables and functions */
 int DIV_ROUND_UP (int,int /*<<< orphan*/ ) ; 
 int SPRD_SPI_FIFO_SIZE ; 
 int USEC_PER_SEC ; 

__attribute__((used)) static u32 sprd_spi_transfer_max_timeout(struct sprd_spi *ss,
					 struct spi_transfer *t)
{
	/*
	 * The time spent on transmission of the full FIFO data is the maximum
	 * SPI transmission time.
	 */
	u32 size = t->bits_per_word * SPRD_SPI_FIFO_SIZE;
	u32 bit_time_us = DIV_ROUND_UP(USEC_PER_SEC, ss->hw_speed_hz);
	u32 total_time_us = size * bit_time_us;
	/*
	 * There is an interval between data and the data in our SPI hardware,
	 * so the total transmission time need add the interval time.
	 */
	u32 interval_cycle = SPRD_SPI_FIFO_SIZE * ss->word_delay;
	u32 interval_time_us = DIV_ROUND_UP(interval_cycle * USEC_PER_SEC,
					    ss->src_clk);

	return total_time_us + interval_time_us;
}