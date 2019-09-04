#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  field; int /*<<< orphan*/  w; } ;
struct TYPE_5__ {TYPE_1__ win; } ;
struct v4l2_format {TYPE_2__ fmt; } ;
struct file {int dummy; } ;
struct TYPE_6__ {int /*<<< orphan*/  field; int /*<<< orphan*/  w; } ;
struct bttv_fh {TYPE_3__ ov; } ;

/* Variables and functions */

__attribute__((used)) static int bttv_g_fmt_vid_overlay(struct file *file, void *priv,
					struct v4l2_format *f)
{
	struct bttv_fh *fh  = priv;

	f->fmt.win.w     = fh->ov.w;
	f->fmt.win.field = fh->ov.field;

	return 0;
}