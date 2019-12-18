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
typedef  int /*<<< orphan*/  u32 ;
struct v4l2_subdev_pad_config {int dummy; } ;
struct v4l2_subdev_format {scalar_t__ pad; int /*<<< orphan*/  format; } ;
struct s5c73m3_frame_size {int dummy; } ;
struct s5c73m3 {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  RES_ISP ; 
 int /*<<< orphan*/  RES_JPEG ; 
 int /*<<< orphan*/  S5C73M3_ISP_FMT ; 
 scalar_t__ S5C73M3_ISP_PAD ; 
 int /*<<< orphan*/  S5C73M3_JPEG_FMT ; 
 int /*<<< orphan*/  s5c73m3_fill_mbus_fmt (int /*<<< orphan*/ *,struct s5c73m3_frame_size const*,int /*<<< orphan*/ ) ; 
 struct s5c73m3_frame_size* s5c73m3_find_frame_size (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void s5c73m3_try_format(struct s5c73m3 *state,
			      struct v4l2_subdev_pad_config *cfg,
			      struct v4l2_subdev_format *fmt,
			      const struct s5c73m3_frame_size **fs)
{
	u32 code;

	if (fmt->pad == S5C73M3_ISP_PAD) {
		*fs = s5c73m3_find_frame_size(&fmt->format, RES_ISP);
		code = S5C73M3_ISP_FMT;
	} else {
		*fs = s5c73m3_find_frame_size(&fmt->format, RES_JPEG);
		code = S5C73M3_JPEG_FMT;
	}

	s5c73m3_fill_mbus_fmt(&fmt->format, *fs, code);
}