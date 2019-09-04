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
struct v4l2_fmtdesc {scalar_t__ type; int index; scalar_t__ pixelformat; } ;
struct file {int dummy; } ;
struct camss_video {scalar_t__ type; int nformats; TYPE_1__* formats; } ;
struct TYPE_2__ {scalar_t__ pixelformat; } ;

/* Variables and functions */
 int EINVAL ; 
 struct camss_video* video_drvdata (struct file*) ; 

__attribute__((used)) static int video_enum_fmt(struct file *file, void *fh, struct v4l2_fmtdesc *f)
{
	struct camss_video *video = video_drvdata(file);
	int i, j, k;

	if (f->type != video->type)
		return -EINVAL;

	if (f->index >= video->nformats)
		return -EINVAL;

	/* find index "i" of "k"th unique pixelformat in formats array */
	k = -1;
	for (i = 0; i < video->nformats; i++) {
		for (j = 0; j < i; j++) {
			if (video->formats[i].pixelformat ==
					video->formats[j].pixelformat)
				break;
		}

		if (j == i)
			k++;

		if (k == f->index)
			break;
	}

	if (k < f->index)
		return -EINVAL;

	f->pixelformat = video->formats[i].pixelformat;

	return 0;
}