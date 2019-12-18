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
struct st_i2c_dev {scalar_t__ base; } ;

/* Variables and functions */
 scalar_t__ SSC_RBUF ; 
 int SSC_RXFIFO_SIZE ; 
 scalar_t__ SSC_RX_FSTAT ; 
 int SSC_RX_FSTAT_STATUS ; 
 scalar_t__ SSC_STA ; 
 int SSC_STA_RIR ; 
 int readl_relaxed (scalar_t__) ; 

__attribute__((used)) static void st_i2c_flush_rx_fifo(struct st_i2c_dev *i2c_dev)
{
	int count, i;

	/*
	 * Counter only counts up to 7 but fifo size is 8...
	 * When fifo is full, counter is 0 and RIR bit of status register is
	 * set
	 */
	if (readl_relaxed(i2c_dev->base + SSC_STA) & SSC_STA_RIR)
		count = SSC_RXFIFO_SIZE;
	else
		count = readl_relaxed(i2c_dev->base + SSC_RX_FSTAT) &
			SSC_RX_FSTAT_STATUS;

	for (i = 0; i < count; i++)
		readl_relaxed(i2c_dev->base + SSC_RBUF);
}