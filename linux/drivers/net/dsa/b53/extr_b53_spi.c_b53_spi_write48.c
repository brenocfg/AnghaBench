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
typedef  int /*<<< orphan*/  u64 ;
typedef  int /*<<< orphan*/  txbuf ;
struct spi_device {int dummy; } ;
struct b53_device {struct spi_device* priv; } ;

/* Variables and functions */
 int B53_SPI_CMD_NORMAL ; 
 int B53_SPI_CMD_WRITE ; 
 int b53_prepare_reg_access (struct spi_device*,int) ; 
 int /*<<< orphan*/  put_unaligned_le64 (int /*<<< orphan*/ ,int*) ; 
 int spi_write (struct spi_device*,int*,int) ; 

__attribute__((used)) static int b53_spi_write48(struct b53_device *dev, u8 page, u8 reg, u64 value)
{
	struct spi_device *spi = dev->priv;
	int ret;
	u8 txbuf[10];

	ret = b53_prepare_reg_access(spi, page);
	if (ret)
		return ret;

	txbuf[0] = B53_SPI_CMD_NORMAL | B53_SPI_CMD_WRITE;
	txbuf[1] = reg;
	put_unaligned_le64(value, &txbuf[2]);

	return spi_write(spi, txbuf, sizeof(txbuf) - 2);
}