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
struct ov5640_mode_info {int hact; int vact; } ;
struct ov5640_dev {int dummy; } ;
typedef  enum ov5640_frame_rate { ____Placeholder_ov5640_frame_rate } ov5640_frame_rate ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int OV5640_60_FPS ; 
 int /*<<< orphan*/  hact ; 
 int /*<<< orphan*/  ov5640_mode_data ; 
 struct ov5640_mode_info* v4l2_find_nearest_size (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  vact ; 

__attribute__((used)) static const struct ov5640_mode_info *
ov5640_find_mode(struct ov5640_dev *sensor, enum ov5640_frame_rate fr,
		 int width, int height, bool nearest)
{
	const struct ov5640_mode_info *mode;

	mode = v4l2_find_nearest_size(ov5640_mode_data,
				      ARRAY_SIZE(ov5640_mode_data),
				      hact, vact,
				      width, height);

	if (!mode ||
	    (!nearest && (mode->hact != width || mode->vact != height)))
		return NULL;

	/* Only 640x480 can operate at 60fps (for now) */
	if (fr == OV5640_60_FPS &&
	    !(mode->hact == 640 && mode->vact == 480))
		return NULL;

	return mode;
}