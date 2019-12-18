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
typedef  size_t u32 ;
struct v4l2_fmtdesc {int type; size_t index; int /*<<< orphan*/  pixelformat; scalar_t__* description; int /*<<< orphan*/  flags; } ;
struct uvc_streaming {int type; size_t nformats; struct uvc_format* format; } ;
struct uvc_format {int flags; int /*<<< orphan*/  fcc; int /*<<< orphan*/  name; } ;
typedef  enum v4l2_buf_type { ____Placeholder_v4l2_buf_type } v4l2_buf_type ;

/* Variables and functions */
 int EINVAL ; 
 int UVC_FMT_FLAG_COMPRESSED ; 
 int /*<<< orphan*/  V4L2_FMT_FLAG_COMPRESSED ; 
 int /*<<< orphan*/  memset (struct v4l2_fmtdesc*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  strscpy (scalar_t__*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int uvc_ioctl_enum_fmt(struct uvc_streaming *stream,
			      struct v4l2_fmtdesc *fmt)
{
	struct uvc_format *format;
	enum v4l2_buf_type type = fmt->type;
	u32 index = fmt->index;

	if (fmt->type != stream->type || fmt->index >= stream->nformats)
		return -EINVAL;

	memset(fmt, 0, sizeof(*fmt));
	fmt->index = index;
	fmt->type = type;

	format = &stream->format[fmt->index];
	fmt->flags = 0;
	if (format->flags & UVC_FMT_FLAG_COMPRESSED)
		fmt->flags |= V4L2_FMT_FLAG_COMPRESSED;
	strscpy(fmt->description, format->name, sizeof(fmt->description));
	fmt->description[sizeof(fmt->description) - 1] = 0;
	fmt->pixelformat = format->fcc;
	return 0;
}