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
 int /*<<< orphan*/  MASK_DATAMODUL_MODE ; 
 int /*<<< orphan*/  REG_DATAMODUL ; 
 int rf69_read_mod_write (struct spi_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int rf69_set_data_mode(struct spi_device *spi, u8 data_mode)
{
	return rf69_read_mod_write(spi, REG_DATAMODUL, MASK_DATAMODUL_MODE,
				   data_mode);
}