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
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_warn (struct device*,char*,unsigned int,...) ; 

__attribute__((used)) static void ati_remote_dump(struct device *dev, unsigned char *data,
			    unsigned int len)
{
	if (len == 1) {
		if (data[0] != (unsigned char)0xff && data[0] != 0x00)
			dev_warn(dev, "Weird byte 0x%02x\n", data[0]);
	} else if (len == 4)
		dev_warn(dev, "Weird key %*ph\n", 4, data);
	else
		dev_warn(dev, "Weird data, len=%d %*ph ...\n", len, 6, data);
}