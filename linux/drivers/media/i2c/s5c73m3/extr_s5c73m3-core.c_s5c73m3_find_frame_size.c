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
struct v4l2_mbus_framefmt {scalar_t__ height; scalar_t__ width; } ;
struct s5c73m3_frame_size {scalar_t__ height; scalar_t__ width; } ;
typedef  enum s5c73m3_resolution_types { ____Placeholder_s5c73m3_resolution_types } s5c73m3_resolution_types ;

/* Variables and functions */
 int INT_MAX ; 
 int abs (scalar_t__) ; 
 struct s5c73m3_frame_size** s5c73m3_resolutions ; 
 int* s5c73m3_resolutions_len ; 

__attribute__((used)) static const struct s5c73m3_frame_size *s5c73m3_find_frame_size(
					struct v4l2_mbus_framefmt *fmt,
					enum s5c73m3_resolution_types idx)
{
	const struct s5c73m3_frame_size *fs;
	const struct s5c73m3_frame_size *best_fs;
	int best_dist = INT_MAX;
	int i;

	fs = s5c73m3_resolutions[idx];
	best_fs = NULL;
	for (i = 0; i < s5c73m3_resolutions_len[idx]; ++i) {
		int dist = abs(fs->width - fmt->width) +
						abs(fs->height - fmt->height);
		if (dist < best_dist) {
			best_dist = dist;
			best_fs = fs;
		}
		++fs;
	}

	return best_fs;
}