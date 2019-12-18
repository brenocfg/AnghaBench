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
struct go7007 {int standard; TYPE_1__* board_info; } ;
struct TYPE_2__ {int sensor_width; int sensor_height; } ;

/* Variables and functions */
#define  GO7007_STD_NTSC 130 
#define  GO7007_STD_OTHER 129 
#define  GO7007_STD_PAL 128 

__attribute__((used)) static void get_resolution(struct go7007 *go, int *width, int *height)
{
	switch (go->standard) {
	case GO7007_STD_NTSC:
		*width = 720;
		*height = 480;
		break;
	case GO7007_STD_PAL:
		*width = 720;
		*height = 576;
		break;
	case GO7007_STD_OTHER:
	default:
		*width = go->board_info->sensor_width;
		*height = go->board_info->sensor_height;
		break;
	}
}