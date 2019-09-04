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
struct w83627hf_data {scalar_t__ vrm; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 struct w83627hf_data* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  sprintf (char*,char*,long) ; 

__attribute__((used)) static ssize_t
vrm_show(struct device *dev, struct device_attribute *attr, char *buf)
{
	struct w83627hf_data *data = dev_get_drvdata(dev);
	return sprintf(buf, "%ld\n", (long) data->vrm);
}