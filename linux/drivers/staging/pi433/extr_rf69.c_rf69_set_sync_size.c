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
struct spi_device {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  MASK_SYNC_CONFIG_SYNC_SIZE ; 
 int /*<<< orphan*/  REG_SYNC_CONFIG ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*) ; 
 int rf69_read_mod_write (struct spi_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

int rf69_set_sync_size(struct spi_device *spi, u8 sync_size)
{
	// check input value
	if (sync_size > 0x07) {
		dev_dbg(&spi->dev, "set: illegal input param");
		return -EINVAL;
	}

	// write value
	return rf69_read_mod_write(spi, REG_SYNC_CONFIG,
				   MASK_SYNC_CONFIG_SYNC_SIZE,
				   (sync_size << 3));
}