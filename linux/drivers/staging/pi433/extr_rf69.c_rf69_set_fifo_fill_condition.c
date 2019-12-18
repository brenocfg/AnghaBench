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
struct spi_device {int /*<<< orphan*/  dev; } ;
typedef  enum fifo_fill_condition { ____Placeholder_fifo_fill_condition } fifo_fill_condition ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  MASK_SYNC_CONFIG_FIFO_FILL_CONDITION ; 
 int /*<<< orphan*/  REG_SYNC_CONFIG ; 
#define  after_sync_interrupt 129 
#define  always 128 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*) ; 
 int rf69_clear_bit (struct spi_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int rf69_set_bit (struct spi_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int rf69_set_fifo_fill_condition(struct spi_device *spi,
				 enum fifo_fill_condition fifo_fill_condition)
{
	switch (fifo_fill_condition) {
	case always:
		return rf69_set_bit(spi, REG_SYNC_CONFIG,
				    MASK_SYNC_CONFIG_FIFO_FILL_CONDITION);
	case after_sync_interrupt:
		return rf69_clear_bit(spi, REG_SYNC_CONFIG,
				      MASK_SYNC_CONFIG_FIFO_FILL_CONDITION);
	default:
		dev_dbg(&spi->dev, "set: illegal input param");
		return -EINVAL;
	}
}