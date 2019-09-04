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
struct ics932s401_data {int* regs; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 int ICS932S401_CPU_ALT ; 
 int ICS932S401_MN_ENABLED ; 
 size_t ICS932S401_REG_CTRL ; 
 int ICS932S401_SRC_ALT ; 
 int calculate_src_freq (struct ics932s401_data*) ; 
 struct ics932s401_data* ics932s401_update_device (struct device*) ; 
 int /*<<< orphan*/  sprintf (char*,char*,int) ; 

__attribute__((used)) static ssize_t show_src_clock_sel(struct device *dev,
				  struct device_attribute *devattr,
				  char *buf)
{
	struct ics932s401_data *data = ics932s401_update_device(dev);
	int freq;

	if (data->regs[ICS932S401_REG_CTRL] & ICS932S401_MN_ENABLED)
		freq = calculate_src_freq(data);
	else
		/* Freq is neatly wrapped up for us */
		if (data->regs[ICS932S401_REG_CTRL] & ICS932S401_CPU_ALT &&
		    data->regs[ICS932S401_REG_CTRL] & ICS932S401_SRC_ALT)
			freq = 96000;
		else
			freq = 100000;

	return sprintf(buf, "%d\n", freq);
}