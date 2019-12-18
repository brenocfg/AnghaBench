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
struct v4l2_fmtdesc {unsigned int index; int /*<<< orphan*/  pixelformat; } ;
struct file {int dummy; } ;
struct cedrus_format {unsigned int capabilities; int directions; int /*<<< orphan*/  pixelformat; } ;
struct cedrus_dev {unsigned int capabilities; } ;
struct cedrus_ctx {struct cedrus_dev* dev; } ;

/* Variables and functions */
 unsigned int CEDRUS_FORMATS_COUNT ; 
 int EINVAL ; 
 struct cedrus_ctx* cedrus_file2ctx (struct file*) ; 
 struct cedrus_format* cedrus_formats ; 

__attribute__((used)) static int cedrus_enum_fmt(struct file *file, struct v4l2_fmtdesc *f,
			   u32 direction)
{
	struct cedrus_ctx *ctx = cedrus_file2ctx(file);
	struct cedrus_dev *dev = ctx->dev;
	unsigned int capabilities = dev->capabilities;
	struct cedrus_format *fmt;
	unsigned int i, index;

	/* Index among formats that match the requested direction. */
	index = 0;

	for (i = 0; i < CEDRUS_FORMATS_COUNT; i++) {
		fmt = &cedrus_formats[i];

		if (fmt->capabilities && (fmt->capabilities & capabilities) !=
		    fmt->capabilities)
			continue;

		if (!(cedrus_formats[i].directions & direction))
			continue;

		if (index == f->index)
			break;

		index++;
	}

	/* Matched format. */
	if (i < CEDRUS_FORMATS_COUNT) {
		f->pixelformat = cedrus_formats[i].pixelformat;

		return 0;
	}

	return -EINVAL;
}