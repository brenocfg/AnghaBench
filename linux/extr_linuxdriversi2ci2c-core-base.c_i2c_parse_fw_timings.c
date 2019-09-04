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
struct i2c_timings {int bus_freq_hz; int scl_rise_ns; int scl_fall_ns; int scl_int_delay_ns; int sda_fall_ns; int sda_hold_ns; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int device_property_read_u32 (struct device*,char*,int*) ; 
 int /*<<< orphan*/  memset (struct i2c_timings*,int /*<<< orphan*/ ,int) ; 

void i2c_parse_fw_timings(struct device *dev, struct i2c_timings *t, bool use_defaults)
{
	int ret;

	memset(t, 0, sizeof(*t));

	ret = device_property_read_u32(dev, "clock-frequency", &t->bus_freq_hz);
	if (ret && use_defaults)
		t->bus_freq_hz = 100000;

	ret = device_property_read_u32(dev, "i2c-scl-rising-time-ns", &t->scl_rise_ns);
	if (ret && use_defaults) {
		if (t->bus_freq_hz <= 100000)
			t->scl_rise_ns = 1000;
		else if (t->bus_freq_hz <= 400000)
			t->scl_rise_ns = 300;
		else
			t->scl_rise_ns = 120;
	}

	ret = device_property_read_u32(dev, "i2c-scl-falling-time-ns", &t->scl_fall_ns);
	if (ret && use_defaults) {
		if (t->bus_freq_hz <= 400000)
			t->scl_fall_ns = 300;
		else
			t->scl_fall_ns = 120;
	}

	device_property_read_u32(dev, "i2c-scl-internal-delay-ns", &t->scl_int_delay_ns);

	ret = device_property_read_u32(dev, "i2c-sda-falling-time-ns", &t->sda_fall_ns);
	if (ret && use_defaults)
		t->sda_fall_ns = t->scl_fall_ns;

	device_property_read_u32(dev, "i2c-sda-hold-time-ns", &t->sda_hold_ns);
}