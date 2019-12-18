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
struct ipu_image_convert_priv {TYPE_1__* ipu; } ;
struct TYPE_6__ {int /*<<< orphan*/  height; int /*<<< orphan*/  width; } ;
struct TYPE_7__ {TYPE_2__ pix; } ;
struct ipu_image_convert_image {scalar_t__ type; TYPE_4__* fmt; int /*<<< orphan*/  num_rows; int /*<<< orphan*/  num_cols; TYPE_3__ base; } ;
struct ipu_image_convert_ctx {struct ipu_image_convert_chan* chan; } ;
struct ipu_image_convert_chan {int /*<<< orphan*/  ic_task; struct ipu_image_convert_priv* priv; } ;
struct TYPE_8__ {int fourcc; } ;
struct TYPE_5__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 scalar_t__ IMAGE_CONVERT_OUT ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,struct ipu_image_convert_ctx*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int,int) ; 

__attribute__((used)) static void dump_format(struct ipu_image_convert_ctx *ctx,
			struct ipu_image_convert_image *ic_image)
{
	struct ipu_image_convert_chan *chan = ctx->chan;
	struct ipu_image_convert_priv *priv = chan->priv;

	dev_dbg(priv->ipu->dev,
		"task %u: ctx %p: %s format: %dx%d (%dx%d tiles), %c%c%c%c\n",
		chan->ic_task, ctx,
		ic_image->type == IMAGE_CONVERT_OUT ? "Output" : "Input",
		ic_image->base.pix.width, ic_image->base.pix.height,
		ic_image->num_cols, ic_image->num_rows,
		ic_image->fmt->fourcc & 0xff,
		(ic_image->fmt->fourcc >> 8) & 0xff,
		(ic_image->fmt->fourcc >> 16) & 0xff,
		(ic_image->fmt->fourcc >> 24) & 0xff);
}