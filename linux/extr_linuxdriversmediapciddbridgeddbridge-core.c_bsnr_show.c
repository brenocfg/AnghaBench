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
struct ddb {int dummy; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  ddbridge_flashread (struct ddb*,int /*<<< orphan*/ ,char*,int,int) ; 
 struct ddb* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  sprintf (char*,char*,char*) ; 

__attribute__((used)) static ssize_t bsnr_show(struct device *device,
			 struct device_attribute *attr, char *buf)
{
	struct ddb *dev = dev_get_drvdata(device);
	char snr[16];

	ddbridge_flashread(dev, 0, snr, 0x10, 15);
	snr[15] = 0; /* in case it is not terminated on EEPROM */
	return sprintf(buf, "%s\n", snr);
}