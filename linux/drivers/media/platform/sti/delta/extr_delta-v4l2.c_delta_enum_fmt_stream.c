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
struct v4l2_fmtdesc {size_t index; int /*<<< orphan*/  pixelformat; } ;
struct file {int /*<<< orphan*/  private_data; } ;
struct delta_dev {size_t nb_of_streamformats; int /*<<< orphan*/ * streamformats; } ;
struct delta_ctx {struct delta_dev* dev; } ;

/* Variables and functions */
 int EINVAL ; 
 struct delta_ctx* to_ctx (int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int delta_enum_fmt_stream(struct file *file, void *priv,
				 struct v4l2_fmtdesc *f)
{
	struct delta_ctx *ctx = to_ctx(file->private_data);
	struct delta_dev *delta = ctx->dev;

	if (unlikely(f->index >= delta->nb_of_streamformats))
		return -EINVAL;

	f->pixelformat = delta->streamformats[f->index];

	return 0;
}