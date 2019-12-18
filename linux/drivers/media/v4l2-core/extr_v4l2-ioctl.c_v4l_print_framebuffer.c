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
struct TYPE_2__ {int pixelformat; int /*<<< orphan*/  colorspace; int /*<<< orphan*/  sizeimage; int /*<<< orphan*/  bytesperline; int /*<<< orphan*/  height; int /*<<< orphan*/  width; } ;
struct v4l2_framebuffer {TYPE_1__ fmt; int /*<<< orphan*/  base; int /*<<< orphan*/  flags; int /*<<< orphan*/  capability; } ;

/* Variables and functions */
 int /*<<< orphan*/  pr_cont (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void v4l_print_framebuffer(const void *arg, bool write_only)
{
	const struct v4l2_framebuffer *p = arg;

	pr_cont("capability=0x%x, flags=0x%x, base=0x%p, width=%u, height=%u, pixelformat=%c%c%c%c, bytesperline=%u, sizeimage=%u, colorspace=%d\n",
			p->capability, p->flags, p->base,
			p->fmt.width, p->fmt.height,
			(p->fmt.pixelformat & 0xff),
			(p->fmt.pixelformat >>  8) & 0xff,
			(p->fmt.pixelformat >> 16) & 0xff,
			(p->fmt.pixelformat >> 24) & 0xff,
			p->fmt.bytesperline, p->fmt.sizeimage,
			p->fmt.colorspace);
}