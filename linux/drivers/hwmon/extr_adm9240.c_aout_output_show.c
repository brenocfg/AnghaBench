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
struct adm9240_data {int /*<<< orphan*/  aout; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 int AOUT_FROM_REG (int /*<<< orphan*/ ) ; 
 struct adm9240_data* adm9240_update_device (struct device*) ; 
 int /*<<< orphan*/  sprintf (char*,char*,int) ; 

__attribute__((used)) static ssize_t aout_output_show(struct device *dev,
				struct device_attribute *attr, char *buf)
{
	struct adm9240_data *data = adm9240_update_device(dev);
	return sprintf(buf, "%d\n", AOUT_FROM_REG(data->aout));
}