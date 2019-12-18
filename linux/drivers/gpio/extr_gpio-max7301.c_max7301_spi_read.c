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
typedef  int u16 ;
struct spi_device {int dummy; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int spi_write_then_read (struct spi_device*,int*,int,int*,int) ; 
 struct spi_device* to_spi_device (struct device*) ; 

__attribute__((used)) static int max7301_spi_read(struct device *dev, unsigned int reg)
{
	int ret;
	u16 word;
	struct spi_device *spi = to_spi_device(dev);

	word = 0x8000 | (reg << 8);
	ret = spi_write_then_read(spi, &word, sizeof(word), &word,
				  sizeof(word));
	if (ret)
		return ret;
	return word & 0xff;
}