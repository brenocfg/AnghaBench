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
struct device {unsigned int id; } ;
typedef  int /*<<< orphan*/  ssize_t ;
struct TYPE_2__ {int /*<<< orphan*/  data3; int /*<<< orphan*/  data2; int /*<<< orphan*/  data1; } ;

/* Variables and functions */
 TYPE_1__* err_data_buffer ; 
 int /*<<< orphan*/  sprintf (char*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static ssize_t
show_err_data_buffer(struct device *dev,
			struct device_attribute *attr, char *buf)
{
	unsigned int cpu=dev->id;

	return sprintf(buf, "%lx, %lx, %lx\n",
			err_data_buffer[cpu].data1,
			err_data_buffer[cpu].data2,
			err_data_buffer[cpu].data3);
}