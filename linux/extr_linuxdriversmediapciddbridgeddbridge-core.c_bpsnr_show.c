#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
struct ddb {TYPE_1__* i2c; int /*<<< orphan*/  i2c_num; } ;
typedef  int /*<<< orphan*/  ssize_t ;
struct TYPE_2__ {int /*<<< orphan*/  adap; } ;

/* Variables and functions */
 struct ddb* dev_get_drvdata (struct device*) ; 
 scalar_t__ i2c_read_regs16 (int /*<<< orphan*/ *,int,int,unsigned char*,int) ; 
 int /*<<< orphan*/  sprintf (char*,char*,...) ; 

__attribute__((used)) static ssize_t bpsnr_show(struct device *device,
			  struct device_attribute *attr, char *buf)
{
	struct ddb *dev = dev_get_drvdata(device);
	unsigned char snr[32];

	if (!dev->i2c_num)
		return 0;

	if (i2c_read_regs16(&dev->i2c[0].adap,
			    0x50, 0x0000, snr, 32) < 0 ||
	    snr[0] == 0xff)
		return sprintf(buf, "NO SNR\n");
	snr[31] = 0; /* in case it is not terminated on EEPROM */
	return sprintf(buf, "%s\n", snr);
}