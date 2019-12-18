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
typedef  int u16 ;
struct spi_device {int dummy; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int TCAN4X5X_READ_CMD ; 
 int spi_write_then_read (struct spi_device*,int*,size_t,int*,size_t) ; 
 struct spi_device* to_spi_device (struct device*) ; 

__attribute__((used)) static int tcan4x5x_regmap_read(void *context,
				const void *reg, size_t reg_size,
				void *val, size_t val_size)
{
	struct device *dev = context;
	struct spi_device *spi = to_spi_device(dev);

	u32 addr = TCAN4X5X_READ_CMD | (*((u16 *)reg) << 8) | val_size >> 2;

	return spi_write_then_read(spi, &addr, reg_size, (u32 *)val, val_size);
}