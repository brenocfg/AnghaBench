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
struct lm93_data {int /*<<< orphan*/  gpi; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 int LM93_GPI_FROM_REG (int /*<<< orphan*/ ) ; 
 struct lm93_data* lm93_update_device (struct device*) ; 
 int /*<<< orphan*/  sprintf (char*,char*,int) ; 

__attribute__((used)) static ssize_t gpio_show(struct device *dev, struct device_attribute *attr,
				char *buf)
{
	struct lm93_data *data = lm93_update_device(dev);
	return sprintf(buf, "%d\n", LM93_GPI_FROM_REG(data->gpi));
}