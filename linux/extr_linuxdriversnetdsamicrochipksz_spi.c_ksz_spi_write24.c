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
typedef  int u32 ;
struct spi_device {int dummy; } ;
struct ksz_device {struct spi_device* priv; } ;

/* Variables and functions */
 int cpu_to_be32 (int) ; 
 int ksz_spi_write_reg (struct spi_device*,int,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int ksz_spi_write24(struct ksz_device *dev, u32 reg, u32 value)
{
	struct spi_device *spi = dev->priv;

	/* make it to big endian 24bit from MSB */
	value <<= 8;
	value = cpu_to_be32(value);
	return ksz_spi_write_reg(spi, reg, (u8 *)&value, 3);
}