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
struct TYPE_2__ {int /*<<< orphan*/  pix_mp; } ;
struct v4l2_format {TYPE_1__ fmt; } ;
struct file {int dummy; } ;
struct ceu_device {int /*<<< orphan*/  v4l2_pix; } ;

/* Variables and functions */
 struct ceu_device* video_drvdata (struct file*) ; 

__attribute__((used)) static int ceu_g_fmt_vid_cap(struct file *file, void *priv,
			     struct v4l2_format *f)
{
	struct ceu_device *ceudev = video_drvdata(file);

	f->fmt.pix_mp = ceudev->v4l2_pix;

	return 0;
}