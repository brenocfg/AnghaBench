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
struct ad7414_data {int /*<<< orphan*/  temp_input; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 int ad7414_temp_from_reg (int /*<<< orphan*/ ) ; 
 struct ad7414_data* ad7414_update_device (struct device*) ; 
 int /*<<< orphan*/  sprintf (char*,char*,int) ; 

__attribute__((used)) static ssize_t temp_input_show(struct device *dev,
			       struct device_attribute *attr, char *buf)
{
	struct ad7414_data *data = ad7414_update_device(dev);
	return sprintf(buf, "%d\n", ad7414_temp_from_reg(data->temp_input));
}