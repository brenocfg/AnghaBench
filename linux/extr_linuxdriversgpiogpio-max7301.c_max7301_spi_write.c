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
typedef  int /*<<< orphan*/  word ;
typedef  unsigned int u16 ;
struct spi_device {int dummy; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int spi_write_then_read (struct spi_device*,unsigned int*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct spi_device* to_spi_device (struct device*) ; 

__attribute__((used)) static int max7301_spi_write(struct device *dev, unsigned int reg,
				unsigned int val)
{
	struct spi_device *spi = to_spi_device(dev);
	u16 word = ((reg & 0x7F) << 8) | (val & 0xFF);

	return spi_write_then_read(spi, &word, sizeof(word), NULL, 0);
}