#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int* name; } ;
struct device_attribute {TYPE_1__ attr; } ;
struct device {int dummy; } ;
struct ddb {TYPE_3__* i2c; TYPE_2__* port; } ;
typedef  int /*<<< orphan*/  ssize_t ;
struct TYPE_6__ {int /*<<< orphan*/  adap; } ;
struct TYPE_5__ {scalar_t__ type; } ;

/* Variables and functions */
 scalar_t__ DDB_TUNER_XO2 ; 
 struct ddb* dev_get_drvdata (struct device*) ; 
 scalar_t__ i2c_read_regs (int /*<<< orphan*/ *,int,int,char*,int) ; 
 scalar_t__ i2c_read_regs16 (int /*<<< orphan*/ *,int,int,char*,int) ; 
 int /*<<< orphan*/  sprintf (char*,char*,...) ; 

__attribute__((used)) static ssize_t snr_show(struct device *device,
			struct device_attribute *attr, char *buf)
{
	struct ddb *dev = dev_get_drvdata(device);
	char snr[32];
	int num = attr->attr.name[3] - 0x30;

	if (dev->port[num].type >= DDB_TUNER_XO2) {
		if (i2c_read_regs(&dev->i2c[num].adap, 0x10, 0x10, snr, 16) < 0)
			return sprintf(buf, "NO SNR\n");
		snr[16] = 0;
	} else {
		/* serial number at 0x100-0x11f */
		if (i2c_read_regs16(&dev->i2c[num].adap,
				    0x57, 0x100, snr, 32) < 0)
			if (i2c_read_regs16(&dev->i2c[num].adap,
					    0x50, 0x100, snr, 32) < 0)
				return sprintf(buf, "NO SNR\n");
		snr[31] = 0; /* in case it is not terminated on EEPROM */
	}
	return sprintf(buf, "%s\n", snr);
}