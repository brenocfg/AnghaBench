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
struct TYPE_2__ {int x; int abs_event; int /*<<< orphan*/  y; } ;
struct mousedev {TYPE_1__ packet; } ;
struct input_dev {int dummy; } ;

/* Variables and functions */
#define  ABS_X 129 
#define  ABS_Y 128 
 int clamp (int,int,int) ; 
 int input_abs_get_max (struct input_dev*,int const) ; 
 int input_abs_get_min (struct input_dev*,int const) ; 
 int xres ; 
 int yres ; 

__attribute__((used)) static void mousedev_abs_event(struct input_dev *dev, struct mousedev *mousedev,
				unsigned int code, int value)
{
	int min, max, size;

	switch (code) {

	case ABS_X:
		min = input_abs_get_min(dev, ABS_X);
		max = input_abs_get_max(dev, ABS_X);

		size = max - min;
		if (size == 0)
			size = xres ? : 1;

		value = clamp(value, min, max);

		mousedev->packet.x = ((value - min) * xres) / size;
		mousedev->packet.abs_event = 1;
		break;

	case ABS_Y:
		min = input_abs_get_min(dev, ABS_Y);
		max = input_abs_get_max(dev, ABS_Y);

		size = max - min;
		if (size == 0)
			size = yres ? : 1;

		value = clamp(value, min, max);

		mousedev->packet.y = yres - ((value - min) * yres) / size;
		mousedev->packet.abs_event = 1;
		break;
	}
}