#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct ipu_image_convert_priv {TYPE_2__* ipu; } ;
struct TYPE_7__ {int /*<<< orphan*/  bytesperline; int /*<<< orphan*/  width; int /*<<< orphan*/  pixelformat; } ;
struct ipu_image {TYPE_3__ pix; } ;
struct ipu_image_convert_image {int type; struct ipu_image base; int /*<<< orphan*/  stride; TYPE_4__* fmt; } ;
struct ipu_image_convert_ctx {TYPE_1__* chan; } ;
typedef  enum ipu_image_convert_type { ____Placeholder_ipu_image_convert_type } ipu_image_convert_type ;
struct TYPE_8__ {scalar_t__ planar; } ;
struct TYPE_6__ {int /*<<< orphan*/  dev; } ;
struct TYPE_5__ {struct ipu_image_convert_priv* priv; } ;

/* Variables and functions */
 int EINVAL ; 
 int IMAGE_CONVERT_OUT ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,char*) ; 
 TYPE_4__* get_format (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int fill_image(struct ipu_image_convert_ctx *ctx,
		      struct ipu_image_convert_image *ic_image,
		      struct ipu_image *image,
		      enum ipu_image_convert_type type)
{
	struct ipu_image_convert_priv *priv = ctx->chan->priv;

	ic_image->base = *image;
	ic_image->type = type;

	ic_image->fmt = get_format(image->pix.pixelformat);
	if (!ic_image->fmt) {
		dev_err(priv->ipu->dev, "pixelformat not supported for %s\n",
			type == IMAGE_CONVERT_OUT ? "Output" : "Input");
		return -EINVAL;
	}

	if (ic_image->fmt->planar)
		ic_image->stride = ic_image->base.pix.width;
	else
		ic_image->stride  = ic_image->base.pix.bytesperline;

	return 0;
}