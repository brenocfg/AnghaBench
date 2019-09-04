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
struct spi_device {int dummy; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int ENOTSUPP ; 
 char const MC13783_AUDIO_CODEC ; 
 char const MC13783_AUDIO_DAC ; 
 int spi_write (struct spi_device*,void const*,size_t) ; 
 struct spi_device* to_spi_device (struct device*) ; 

__attribute__((used)) static int mc13xxx_spi_write(void *context, const void *data, size_t count)
{
	struct device *dev = context;
	struct spi_device *spi = to_spi_device(dev);
	const char *reg = data;

	if (count != 4)
		return -ENOTSUPP;

	/* include errata fix for spi audio problems */
	if (*reg == MC13783_AUDIO_CODEC || *reg == MC13783_AUDIO_DAC)
		spi_write(spi, data, count);

	return spi_write(spi, data, count);
}