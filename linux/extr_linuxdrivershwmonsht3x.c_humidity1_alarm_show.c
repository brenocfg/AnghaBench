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
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  PAGE_SIZE ; 
 int SHT3X_CRC8_LEN ; 
 int SHT3X_WORD_LEN ; 
 int scnprintf (char*,int /*<<< orphan*/ ,char*,int) ; 
 int status_register_read (struct device*,struct device_attribute*,char*,int) ; 

__attribute__((used)) static ssize_t humidity1_alarm_show(struct device *dev,
				    struct device_attribute *attr,
				    char *buf)
{
	char buffer[SHT3X_WORD_LEN + SHT3X_CRC8_LEN];
	int ret;

	ret = status_register_read(dev, attr, buffer,
				   SHT3X_WORD_LEN + SHT3X_CRC8_LEN);
	if (ret)
		return ret;

	return scnprintf(buf, PAGE_SIZE, "%d\n", !!(buffer[0] & 0x08));
}