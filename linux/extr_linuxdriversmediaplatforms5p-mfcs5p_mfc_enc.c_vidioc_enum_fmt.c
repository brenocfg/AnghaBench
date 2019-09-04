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
struct v4l2_fmtdesc {int index; int /*<<< orphan*/  pixelformat; int /*<<< orphan*/  description; } ;
struct s5p_mfc_fmt {scalar_t__ type; int versions; int /*<<< orphan*/  fourcc; int /*<<< orphan*/  name; } ;
struct s5p_mfc_dev {TYPE_1__* variant; } ;
struct file {int dummy; } ;
struct TYPE_2__ {int version_bit; } ;

/* Variables and functions */
 int ARRAY_SIZE (struct s5p_mfc_fmt*) ; 
 int EINVAL ; 
 scalar_t__ MFC_FMT_ENC ; 
 scalar_t__ MFC_FMT_RAW ; 
 struct s5p_mfc_fmt* formats ; 
 int /*<<< orphan*/  strlcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 struct s5p_mfc_dev* video_drvdata (struct file*) ; 

__attribute__((used)) static int vidioc_enum_fmt(struct file *file, struct v4l2_fmtdesc *f,
							bool out)
{
	struct s5p_mfc_dev *dev = video_drvdata(file);
	struct s5p_mfc_fmt *fmt;
	int i, j = 0;

	for (i = 0; i < ARRAY_SIZE(formats); ++i) {
		if (out && formats[i].type != MFC_FMT_RAW)
			continue;
		else if (!out && formats[i].type != MFC_FMT_ENC)
			continue;
		else if ((dev->variant->version_bit & formats[i].versions) == 0)
			continue;

		if (j == f->index) {
			fmt = &formats[i];
			strlcpy(f->description, fmt->name,
				sizeof(f->description));
			f->pixelformat = fmt->fourcc;
			return 0;
		}
		++j;
	}
	return -EINVAL;
}