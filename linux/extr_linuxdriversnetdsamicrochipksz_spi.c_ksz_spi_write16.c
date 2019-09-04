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
typedef  int /*<<< orphan*/  u32 ;
typedef  int /*<<< orphan*/  u16 ;
struct spi_device {int dummy; } ;
struct ksz_device {struct spi_device* priv; } ;

/* Variables and functions */
 int /*<<< orphan*/  cpu_to_be16 (int /*<<< orphan*/ ) ; 
 int ksz_spi_write_reg (struct spi_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int ksz_spi_write16(struct ksz_device *dev, u32 reg, u16 value)
{
	struct spi_device *spi = dev->priv;

	value = cpu_to_be16(value);
	return ksz_spi_write_reg(spi, reg, (u8 *)&value, 2);
}