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
struct hva_dev {size_t nb_of_streamformats; int /*<<< orphan*/ * streamformats; } ;
struct hva_ctx {int dummy; } ;
struct file {int /*<<< orphan*/  private_data; } ;

/* Variables and functions */
 int EINVAL ; 
 struct hva_dev* ctx_to_hdev (struct hva_ctx*) ; 
 struct hva_ctx* fh_to_ctx (int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int hva_enum_fmt_stream(struct file *file, void *priv,
			       struct v4l2_fmtdesc *f)
{
	struct hva_ctx *ctx = fh_to_ctx(file->private_data);
	struct hva_dev *hva = ctx_to_hdev(ctx);

	if (unlikely(f->index >= hva->nb_of_streamformats))
		return -EINVAL;

	f->pixelformat = hva->streamformats[f->index];

	return 0;
}