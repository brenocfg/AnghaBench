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
struct v4l2_fmtdesc {size_t index; int /*<<< orphan*/  pixelformat; } ;
struct stm32_dcmi {size_t num_of_sd_formats; TYPE_1__** sd_formats; } ;
struct file {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  fourcc; } ;

/* Variables and functions */
 int EINVAL ; 
 struct stm32_dcmi* video_drvdata (struct file*) ; 

__attribute__((used)) static int dcmi_enum_fmt_vid_cap(struct file *file, void  *priv,
				 struct v4l2_fmtdesc *f)
{
	struct stm32_dcmi *dcmi = video_drvdata(file);

	if (f->index >= dcmi->num_of_sd_formats)
		return -EINVAL;

	f->pixelformat = dcmi->sd_formats[f->index]->fourcc;
	return 0;
}