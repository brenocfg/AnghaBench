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
struct TYPE_2__ {int /*<<< orphan*/  pix; } ;
struct v4l2_format {TYPE_1__ fmt; } ;
struct sur40_state {int /*<<< orphan*/  pix_fmt; } ;
struct file {int dummy; } ;

/* Variables and functions */
 struct sur40_state* video_drvdata (struct file*) ; 

__attribute__((used)) static int sur40_vidioc_g_fmt(struct file *file, void *priv,
			    struct v4l2_format *f)
{
	struct sur40_state *sur40 = video_drvdata(file);

	f->fmt.pix = sur40->pix_fmt;
	return 0;
}