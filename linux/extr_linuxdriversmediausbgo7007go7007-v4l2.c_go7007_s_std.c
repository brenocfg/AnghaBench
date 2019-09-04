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
struct go7007 {int std; int sensor_framerate; int /*<<< orphan*/  v4l2_dev; int /*<<< orphan*/  standard; } ;

/* Variables and functions */
 int /*<<< orphan*/  GO7007_STD_NTSC ; 
 int /*<<< orphan*/  GO7007_STD_PAL ; 
 int V4L2_STD_625_50 ; 
 int /*<<< orphan*/  call_all (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  s_std ; 
 int /*<<< orphan*/  set_capture_size (struct go7007*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  video ; 

__attribute__((used)) static int go7007_s_std(struct go7007 *go)
{
	if (go->std & V4L2_STD_625_50) {
		go->standard = GO7007_STD_PAL;
		go->sensor_framerate = 25025;
	} else {
		go->standard = GO7007_STD_NTSC;
		go->sensor_framerate = 30000;
	}

	call_all(&go->v4l2_dev, video, s_std, go->std);
	set_capture_size(go, NULL, 0);
	return 0;
}