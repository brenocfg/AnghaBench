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
struct tw686x_video_channel {size_t ch; int /*<<< orphan*/  video_standard; int /*<<< orphan*/  fps; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  TW686X_MAX_FPS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * VIDEO_FIELD_CTRL ; 
 int /*<<< orphan*/ * fps_map ; 
 int /*<<< orphan*/  reg_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 unsigned int tw686x_fps_idx (unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tw686x_real_fps (unsigned int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void tw686x_set_framerate(struct tw686x_video_channel *vc,
				 unsigned int fps)
{
	unsigned int i;

	i = tw686x_fps_idx(fps, TW686X_MAX_FPS(vc->video_standard));
	reg_write(vc->dev, VIDEO_FIELD_CTRL[vc->ch], fps_map[i]);
	vc->fps = tw686x_real_fps(i, TW686X_MAX_FPS(vc->video_standard));
}