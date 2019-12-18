#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  buttons; } ;
struct mousedev {TYPE_1__ packet; } ;
struct TYPE_5__ {int /*<<< orphan*/  buttons; } ;
struct TYPE_6__ {TYPE_2__ packet; } ;

/* Variables and functions */
#define  BTN_0 142 
#define  BTN_1 141 
#define  BTN_2 140 
#define  BTN_3 139 
#define  BTN_4 138 
#define  BTN_BACK 137 
#define  BTN_EXTRA 136 
#define  BTN_FORWARD 135 
#define  BTN_LEFT 134 
#define  BTN_MIDDLE 133 
#define  BTN_RIGHT 132 
#define  BTN_SIDE 131 
#define  BTN_STYLUS 130 
#define  BTN_STYLUS2 129 
#define  BTN_TOUCH 128 
 int /*<<< orphan*/  clear_bit (int,int /*<<< orphan*/ *) ; 
 TYPE_3__* mousedev_mix ; 
 int /*<<< orphan*/  set_bit (int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void mousedev_key_event(struct mousedev *mousedev,
				unsigned int code, int value)
{
	int index;

	switch (code) {

	case BTN_TOUCH:
	case BTN_0:
	case BTN_LEFT:		index = 0; break;

	case BTN_STYLUS:
	case BTN_1:
	case BTN_RIGHT:		index = 1; break;

	case BTN_2:
	case BTN_FORWARD:
	case BTN_STYLUS2:
	case BTN_MIDDLE:	index = 2; break;

	case BTN_3:
	case BTN_BACK:
	case BTN_SIDE:		index = 3; break;

	case BTN_4:
	case BTN_EXTRA:		index = 4; break;

	default:		return;
	}

	if (value) {
		set_bit(index, &mousedev->packet.buttons);
		set_bit(index, &mousedev_mix->packet.buttons);
	} else {
		clear_bit(index, &mousedev->packet.buttons);
		clear_bit(index, &mousedev_mix->packet.buttons);
	}
}