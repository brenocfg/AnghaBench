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
struct max31722_data {int /*<<< orphan*/  spi_device; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  scalar_t__ ssize_t ;
typedef  int s16 ;

/* Variables and functions */
 int /*<<< orphan*/  MAX31722_REG_TEMP_LSB ; 
 struct max31722_data* dev_get_drvdata (struct device*) ; 
 scalar_t__ le16_to_cpu (scalar_t__) ; 
 scalar_t__ spi_w8r16 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ sprintf (char*,char*,int) ; 

__attribute__((used)) static ssize_t max31722_temp_show(struct device *dev,
				  struct device_attribute *attr, char *buf)
{
	ssize_t ret;
	struct max31722_data *data = dev_get_drvdata(dev);

	ret = spi_w8r16(data->spi_device, MAX31722_REG_TEMP_LSB);
	if (ret < 0)
		return ret;
	/* Keep 12 bits and multiply by the scale of 62.5 millidegrees/bit. */
	return sprintf(buf, "%d\n", (s16)le16_to_cpu(ret) * 125 / 32);
}