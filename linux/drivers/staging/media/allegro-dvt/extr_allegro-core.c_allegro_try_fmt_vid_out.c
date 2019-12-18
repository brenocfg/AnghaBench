#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int width; int height; int bytesperline; int sizeimage; int /*<<< orphan*/  pixelformat; int /*<<< orphan*/  field; } ;
struct TYPE_4__ {TYPE_1__ pix; } ;
struct v4l2_format {TYPE_2__ fmt; } ;
struct file {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ALLEGRO_HEIGHT_MAX ; 
 int /*<<< orphan*/  ALLEGRO_HEIGHT_MIN ; 
 int /*<<< orphan*/  ALLEGRO_WIDTH_MAX ; 
 int /*<<< orphan*/  ALLEGRO_WIDTH_MIN ; 
 int /*<<< orphan*/  V4L2_FIELD_NONE ; 
 int /*<<< orphan*/  V4L2_PIX_FMT_NV12 ; 
 int /*<<< orphan*/  __u32 ; 
 void* clamp_t (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int round_up (int,int) ; 

__attribute__((used)) static int allegro_try_fmt_vid_out(struct file *file, void *fh,
				   struct v4l2_format *f)
{
	f->fmt.pix.field = V4L2_FIELD_NONE;

	/*
	 * The firmware of the Allegro codec handles the padding internally
	 * and expects the visual frame size when configuring a channel.
	 * Therefore, unlike other encoder drivers, this driver does not round
	 * up the width and height to macroblock alignment and does not
	 * implement the selection api.
	 */
	f->fmt.pix.width = clamp_t(__u32, f->fmt.pix.width,
				   ALLEGRO_WIDTH_MIN, ALLEGRO_WIDTH_MAX);
	f->fmt.pix.height = clamp_t(__u32, f->fmt.pix.height,
				    ALLEGRO_HEIGHT_MIN, ALLEGRO_HEIGHT_MAX);

	f->fmt.pix.pixelformat = V4L2_PIX_FMT_NV12;
	f->fmt.pix.bytesperline = round_up(f->fmt.pix.width, 32);
	f->fmt.pix.sizeimage =
		f->fmt.pix.bytesperline * f->fmt.pix.height * 3 / 2;

	return 0;
}