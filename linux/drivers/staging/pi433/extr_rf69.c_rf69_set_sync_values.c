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
typedef  int /*<<< orphan*/  u8 ;
struct spi_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  REG_SYNCVALUE1 ; 
 int /*<<< orphan*/  REG_SYNCVALUE2 ; 
 int /*<<< orphan*/  REG_SYNCVALUE3 ; 
 int /*<<< orphan*/  REG_SYNCVALUE4 ; 
 int /*<<< orphan*/  REG_SYNCVALUE5 ; 
 int /*<<< orphan*/  REG_SYNCVALUE6 ; 
 int /*<<< orphan*/  REG_SYNCVALUE7 ; 
 int /*<<< orphan*/  REG_SYNCVALUE8 ; 
 scalar_t__ rf69_write_reg (struct spi_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int rf69_set_sync_values(struct spi_device *spi, u8 sync_values[8])
{
	int retval = 0;

	retval += rf69_write_reg(spi, REG_SYNCVALUE1, sync_values[0]);
	retval += rf69_write_reg(spi, REG_SYNCVALUE2, sync_values[1]);
	retval += rf69_write_reg(spi, REG_SYNCVALUE3, sync_values[2]);
	retval += rf69_write_reg(spi, REG_SYNCVALUE4, sync_values[3]);
	retval += rf69_write_reg(spi, REG_SYNCVALUE5, sync_values[4]);
	retval += rf69_write_reg(spi, REG_SYNCVALUE6, sync_values[5]);
	retval += rf69_write_reg(spi, REG_SYNCVALUE7, sync_values[6]);
	retval += rf69_write_reg(spi, REG_SYNCVALUE8, sync_values[7]);

	return retval;
}