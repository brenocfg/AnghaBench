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
typedef  int u32 ;
struct v4l2_pix_format {int width; int /*<<< orphan*/  pixelformat; } ;
struct rvin_video_format {int bpp; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ WARN_ON (int) ; 
 struct rvin_video_format* rvin_format_from_pixel (int /*<<< orphan*/ ) ; 

__attribute__((used)) static u32 rvin_format_bytesperline(struct v4l2_pix_format *pix)
{
	const struct rvin_video_format *fmt;

	fmt = rvin_format_from_pixel(pix->pixelformat);

	if (WARN_ON(!fmt))
		return -EINVAL;

	return pix->width * fmt->bpp;
}