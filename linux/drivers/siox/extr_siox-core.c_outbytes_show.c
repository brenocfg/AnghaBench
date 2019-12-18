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
struct siox_device {int /*<<< orphan*/  outbytes; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  sprintf (char*,char*,int /*<<< orphan*/ ) ; 
 struct siox_device* to_siox_device (struct device*) ; 

__attribute__((used)) static ssize_t outbytes_show(struct device *dev,
			     struct device_attribute *attr, char *buf)
{
	struct siox_device *sdev = to_siox_device(dev);

	return sprintf(buf, "%zu\n", sdev->outbytes);
}