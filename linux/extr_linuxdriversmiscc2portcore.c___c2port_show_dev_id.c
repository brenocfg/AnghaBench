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
struct c2port_device {int dummy; } ;
typedef  int ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  C2PORT_DEVICEID ; 
 int c2port_read_dr (struct c2port_device*,int*) ; 
 int /*<<< orphan*/  c2port_write_ar (struct c2port_device*,int /*<<< orphan*/ ) ; 
 int sprintf (char*,char*,int) ; 

__attribute__((used)) static ssize_t __c2port_show_dev_id(struct c2port_device *dev, char *buf)
{
	u8 data;
	int ret;

	/* Select DEVICEID register for C2 data register accesses */
	c2port_write_ar(dev, C2PORT_DEVICEID);

	/* Read and return the device ID register */
	ret = c2port_read_dr(dev, &data);
	if (ret < 0)
		return ret;

	return sprintf(buf, "%d\n", data);
}