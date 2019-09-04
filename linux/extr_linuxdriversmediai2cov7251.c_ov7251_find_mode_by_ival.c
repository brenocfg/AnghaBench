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
struct v4l2_fract {int dummy; } ;
struct ov7251_mode_info {scalar_t__ width; scalar_t__ height; struct v4l2_fract timeperframe; } ;
struct ov7251 {struct ov7251_mode_info* current_mode; } ;

/* Variables and functions */
 unsigned int ARRAY_SIZE (struct ov7251_mode_info const*) ; 
 unsigned int abs (unsigned int) ; 
 unsigned int avg_fps (struct v4l2_fract*) ; 
 struct ov7251_mode_info const* ov7251_mode_info_data ; 

__attribute__((used)) static const struct ov7251_mode_info *
ov7251_find_mode_by_ival(struct ov7251 *ov7251, struct v4l2_fract *timeperframe)
{
	const struct ov7251_mode_info *mode = ov7251->current_mode;
	unsigned int fps_req = avg_fps(timeperframe);
	unsigned int max_dist_match = (unsigned int) -1;
	unsigned int i, n = 0;

	for (i = 0; i < ARRAY_SIZE(ov7251_mode_info_data); i++) {
		unsigned int dist;
		unsigned int fps_tmp;

		if (mode->width != ov7251_mode_info_data[i].width ||
		    mode->height != ov7251_mode_info_data[i].height)
			continue;

		fps_tmp = avg_fps(&ov7251_mode_info_data[i].timeperframe);

		dist = abs(fps_req - fps_tmp);

		if (dist < max_dist_match) {
			n = i;
			max_dist_match = dist;
		}
	}

	return &ov7251_mode_info_data[n];
}