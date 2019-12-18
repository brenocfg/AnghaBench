#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int numerator; int denominator; } ;
struct TYPE_8__ {int numerator; int denominator; } ;
struct TYPE_7__ {int numerator; int denominator; } ;
struct TYPE_10__ {TYPE_4__ step; TYPE_3__ max; TYPE_2__ min; } ;
struct v4l2_frmivalenum {scalar_t__ pixel_format; TYPE_5__ stepwise; int /*<<< orphan*/  type; scalar_t__ index; } ;
struct file {int dummy; } ;
struct coda_ctx {TYPE_1__* cvd; int /*<<< orphan*/  vdoa; } ;
struct TYPE_6__ {scalar_t__* src_formats; scalar_t__* dst_formats; } ;

/* Variables and functions */
 int CODA_MAX_FORMATS ; 
 int EINVAL ; 
 int /*<<< orphan*/  V4L2_FRMIVAL_TYPE_CONTINUOUS ; 
 scalar_t__ V4L2_PIX_FMT_YUYV ; 
 struct coda_ctx* fh_to_ctx (void*) ; 

__attribute__((used)) static int coda_enum_frameintervals(struct file *file, void *fh,
				    struct v4l2_frmivalenum *f)
{
	struct coda_ctx *ctx = fh_to_ctx(fh);
	int i;

	if (f->index)
		return -EINVAL;

	/* Disallow YUYV if the vdoa is not available */
	if (!ctx->vdoa && f->pixel_format == V4L2_PIX_FMT_YUYV)
		return -EINVAL;

	for (i = 0; i < CODA_MAX_FORMATS; i++) {
		if (f->pixel_format == ctx->cvd->src_formats[i] ||
		    f->pixel_format == ctx->cvd->dst_formats[i])
			break;
	}
	if (i == CODA_MAX_FORMATS)
		return -EINVAL;

	f->type = V4L2_FRMIVAL_TYPE_CONTINUOUS;
	f->stepwise.min.numerator = 1;
	f->stepwise.min.denominator = 65535;
	f->stepwise.max.numerator = 65536;
	f->stepwise.max.denominator = 1;
	f->stepwise.step.numerator = 1;
	f->stepwise.step.denominator = 1;

	return 0;
}