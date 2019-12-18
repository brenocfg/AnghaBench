#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  size_t u32 ;
struct v4l2_fmtdesc {size_t index; int /*<<< orphan*/  pixelformat; } ;
struct file {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  fourcc; int /*<<< orphan*/  sd_support; int /*<<< orphan*/  mbus_code; } ;

/* Variables and functions */
 size_t ARRAY_SIZE (TYPE_1__*) ; 
 int EINVAL ; 
 int /*<<< orphan*/  ISC_IS_FORMAT_RAW (int /*<<< orphan*/ ) ; 
 TYPE_1__* controller_formats ; 
 TYPE_1__* formats_list ; 

__attribute__((used)) static int isc_enum_fmt_vid_cap(struct file *file, void *priv,
				 struct v4l2_fmtdesc *f)
{
	u32 index = f->index;
	u32 i, supported_index;

	if (index < ARRAY_SIZE(controller_formats)) {
		f->pixelformat = controller_formats[index].fourcc;
		return 0;
	}

	index -= ARRAY_SIZE(controller_formats);

	i = 0;
	supported_index = 0;

	for (i = 0; i < ARRAY_SIZE(formats_list); i++) {
		if (!ISC_IS_FORMAT_RAW(formats_list[i].mbus_code) ||
		    !formats_list[i].sd_support)
			continue;
		if (supported_index == index) {
			f->pixelformat = formats_list[i].fourcc;
			return 0;
		}
		supported_index++;
	}

	return -EINVAL;
}