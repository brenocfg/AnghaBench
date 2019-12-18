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
struct TYPE_2__ {int dx; int dy; int dz; } ;
struct mousedev {TYPE_1__ packet; } ;

/* Variables and functions */
#define  REL_WHEEL 130 
#define  REL_X 129 
#define  REL_Y 128 

__attribute__((used)) static void mousedev_rel_event(struct mousedev *mousedev,
				unsigned int code, int value)
{
	switch (code) {
	case REL_X:
		mousedev->packet.dx += value;
		break;

	case REL_Y:
		mousedev->packet.dy -= value;
		break;

	case REL_WHEEL:
		mousedev->packet.dz -= value;
		break;
	}
}