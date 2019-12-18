#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_8__ ;
typedef  struct TYPE_15__   TYPE_7__ ;
typedef  struct TYPE_14__   TYPE_6__ ;
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct v4l2_subdev_format {int /*<<< orphan*/  format; int /*<<< orphan*/  which; int /*<<< orphan*/  pad; } ;
struct v4l2_rect {scalar_t__ width; scalar_t__ height; } ;
struct TYPE_16__ {scalar_t__ width; scalar_t__ height; } ;
struct TYPE_12__ {TYPE_8__ pix; } ;
struct v4l2_format {TYPE_4__ fmt; } ;
struct imx_media_pixfmt {scalar_t__ cs; } ;
struct TYPE_14__ {scalar_t__ width; scalar_t__ height; } ;
struct TYPE_9__ {scalar_t__ width; scalar_t__ height; } ;
struct TYPE_10__ {TYPE_1__ pix; } ;
struct TYPE_11__ {TYPE_2__ fmt; } ;
struct TYPE_15__ {TYPE_6__ compose; TYPE_5__* cc; TYPE_3__ fmt; } ;
struct capture_priv {TYPE_7__ vdev; int /*<<< orphan*/  src_sd; int /*<<< orphan*/  src_sd_pad; } ;
struct TYPE_13__ {scalar_t__ cs; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  V4L2_SUBDEV_FORMAT_ACTIVE ; 
 int __capture_try_fmt_vid_cap (struct capture_priv*,struct v4l2_subdev_format*,struct v4l2_format*,struct imx_media_pixfmt const**,struct v4l2_rect*) ; 
 int /*<<< orphan*/  get_fmt ; 
 int /*<<< orphan*/  pad ; 
 int /*<<< orphan*/  v4l2_fill_pix_format (TYPE_8__*,int /*<<< orphan*/ *) ; 
 int v4l2_subdev_call (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct v4l2_subdev_format*) ; 

__attribute__((used)) static int capture_validate_fmt(struct capture_priv *priv)
{
	struct v4l2_subdev_format fmt_src;
	const struct imx_media_pixfmt *cc;
	struct v4l2_rect compose;
	struct v4l2_format f;
	int ret;

	fmt_src.pad = priv->src_sd_pad;
	fmt_src.which = V4L2_SUBDEV_FORMAT_ACTIVE;
	ret = v4l2_subdev_call(priv->src_sd, pad, get_fmt, NULL, &fmt_src);
	if (ret)
		return ret;

	v4l2_fill_pix_format(&f.fmt.pix, &fmt_src.format);

	ret = __capture_try_fmt_vid_cap(priv, &fmt_src, &f, &cc, &compose);
	if (ret)
		return ret;

	return (priv->vdev.fmt.fmt.pix.width != f.fmt.pix.width ||
		priv->vdev.fmt.fmt.pix.height != f.fmt.pix.height ||
		priv->vdev.cc->cs != cc->cs ||
		priv->vdev.compose.width != compose.width ||
		priv->vdev.compose.height != compose.height) ? -EINVAL : 0;
}