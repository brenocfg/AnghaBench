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
struct go7007_board_info {int sensor_flags; int sensor_width; int sensor_height; int sensor_framerate; int /*<<< orphan*/  sensor_h_offset; int /*<<< orphan*/  sensor_v_offset; } ;
struct go7007 {int width; int height; int sensor_framerate; int /*<<< orphan*/  encoder_h_offset; int /*<<< orphan*/  encoder_v_offset; int /*<<< orphan*/  standard; int /*<<< orphan*/  std; struct go7007_board_info* board_info; } ;

/* Variables and functions */
 int GO7007_SENSOR_TV ; 
 int /*<<< orphan*/  GO7007_STD_NTSC ; 
 int /*<<< orphan*/  GO7007_STD_OTHER ; 
 int /*<<< orphan*/  V4L2_STD_NTSC_M ; 

void go7007_update_board(struct go7007 *go)
{
	const struct go7007_board_info *board = go->board_info;

	if (board->sensor_flags & GO7007_SENSOR_TV) {
		go->standard = GO7007_STD_NTSC;
		go->std = V4L2_STD_NTSC_M;
		go->width = 720;
		go->height = 480;
		go->sensor_framerate = 30000;
	} else {
		go->standard = GO7007_STD_OTHER;
		go->width = board->sensor_width;
		go->height = board->sensor_height;
		go->sensor_framerate = board->sensor_framerate;
	}
	go->encoder_v_offset = board->sensor_v_offset;
	go->encoder_h_offset = board->sensor_h_offset;
}