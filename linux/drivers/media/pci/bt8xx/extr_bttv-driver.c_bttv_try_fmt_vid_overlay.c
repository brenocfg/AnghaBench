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
struct TYPE_2__ {int /*<<< orphan*/  win; } ;
struct v4l2_format {TYPE_1__ fmt; } ;
struct file {int dummy; } ;
struct bttv_fh {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  verify_window_lock (struct bttv_fh*,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int bttv_try_fmt_vid_overlay(struct file *file, void *priv,
						struct v4l2_format *f)
{
	struct bttv_fh *fh = priv;

	verify_window_lock(fh, &f->fmt.win,
			/* adjust_size */ 1,
			/* adjust_crop */ 0);
	return 0;
}