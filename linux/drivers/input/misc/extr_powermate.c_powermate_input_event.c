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
struct powermate_device {int dummy; } ;
struct input_dev {int dummy; } ;

/* Variables and functions */
 unsigned int EV_MSC ; 
 unsigned int MSC_PULSELED ; 
 struct powermate_device* input_get_drvdata (struct input_dev*) ; 
 int /*<<< orphan*/  powermate_pulse_led (struct powermate_device*,int,int,int,int,int) ; 

__attribute__((used)) static int powermate_input_event(struct input_dev *dev, unsigned int type, unsigned int code, int _value)
{
	unsigned int command = (unsigned int)_value;
	struct powermate_device *pm = input_get_drvdata(dev);

	if (type == EV_MSC && code == MSC_PULSELED){
		/*
		    bits  0- 7: 8 bits: LED brightness
		    bits  8-16: 9 bits: pulsing speed modifier (0 ... 510); 0-254 = slower, 255 = standard, 256-510 = faster.
		    bits 17-18: 2 bits: pulse table (0, 1, 2 valid)
		    bit     19: 1 bit : pulse whilst asleep?
		    bit     20: 1 bit : pulse constantly?
		*/
		int static_brightness = command & 0xFF;   // bits 0-7
		int pulse_speed = (command >> 8) & 0x1FF; // bits 8-16
		int pulse_table = (command >> 17) & 0x3;  // bits 17-18
		int pulse_asleep = (command >> 19) & 0x1; // bit 19
		int pulse_awake  = (command >> 20) & 0x1; // bit 20

		powermate_pulse_led(pm, static_brightness, pulse_speed, pulse_table, pulse_asleep, pulse_awake);
	}

	return 0;
}