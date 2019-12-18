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
typedef  int u8 ;
struct pc87427_data {int* address; int* pwm_enable; unsigned long* pwm; int /*<<< orphan*/  lock; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  size_t ssize_t ;
struct TYPE_2__ {int index; } ;

/* Variables and functions */
 size_t EINVAL ; 
 size_t EPERM ; 
 size_t LD_FAN ; 
 scalar_t__ PC87427_REG_PWM_DUTY ; 
 int PWM_ENABLE_MODE_MASK ; 
 int PWM_MODE_MANUAL ; 
 int PWM_MODE_OFF ; 
 int /*<<< orphan*/  dev_dbg (struct device*,char*,int,char*,char*) ; 
 struct pc87427_data* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  dev_notice (struct device*,char*,int) ; 
 scalar_t__ kstrtoul (char const*,int,unsigned long*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  outb (unsigned long,scalar_t__) ; 
 int /*<<< orphan*/  pc87427_readall_pwm (struct pc87427_data*,int) ; 
 TYPE_1__* to_sensor_dev_attr (struct device_attribute*) ; 
 int /*<<< orphan*/  update_pwm_enable (struct pc87427_data*,int,int) ; 

__attribute__((used)) static ssize_t pwm_store(struct device *dev, struct device_attribute *devattr,
			 const char *buf, size_t count)
{
	struct pc87427_data *data = dev_get_drvdata(dev);
	int nr = to_sensor_dev_attr(devattr)->index;
	unsigned long val;
	int iobase = data->address[LD_FAN];
	u8 mode;

	if (kstrtoul(buf, 10, &val) < 0 || val > 0xff)
		return -EINVAL;

	mutex_lock(&data->lock);
	pc87427_readall_pwm(data, nr);
	mode = data->pwm_enable[nr] & PWM_ENABLE_MODE_MASK;
	if (mode != PWM_MODE_MANUAL && mode != PWM_MODE_OFF) {
		dev_notice(dev,
			   "Can't set PWM%d duty cycle while not in manual mode\n",
			   nr + 1);
		mutex_unlock(&data->lock);
		return -EPERM;
	}

	/* We may have to change the mode */
	if (mode == PWM_MODE_MANUAL && val == 0) {
		/* Transition from Manual to Off */
		update_pwm_enable(data, nr, PWM_MODE_OFF);
		mode = PWM_MODE_OFF;
		dev_dbg(dev, "Switching PWM%d from %s to %s\n", nr + 1,
			"manual", "off");
	} else if (mode == PWM_MODE_OFF && val != 0) {
		/* Transition from Off to Manual */
		update_pwm_enable(data, nr, PWM_MODE_MANUAL);
		mode = PWM_MODE_MANUAL;
		dev_dbg(dev, "Switching PWM%d from %s to %s\n", nr + 1,
			"off", "manual");
	}

	data->pwm[nr] = val;
	if (mode == PWM_MODE_MANUAL)
		outb(val, iobase + PC87427_REG_PWM_DUTY);
	mutex_unlock(&data->lock);

	return count;
}