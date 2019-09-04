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
struct spi_device {int dummy; } ;
struct ksz_device {struct spi_device* priv; } ;

/* Variables and functions */
 int ksz_spi_read_reg (struct spi_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,unsigned int) ; 

__attribute__((used)) static int ksz_spi_read(struct ksz_device *dev, u32 reg, u8 *data,
			unsigned int len)
{
	struct spi_device *spi = dev->priv;

	return ksz_spi_read_reg(spi, reg, data, len);
}