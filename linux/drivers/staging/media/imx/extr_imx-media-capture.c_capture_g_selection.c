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
struct TYPE_10__ {int /*<<< orphan*/  height; int /*<<< orphan*/  width; int /*<<< orphan*/  top; int /*<<< orphan*/  left; } ;
struct v4l2_selection {int target; TYPE_5__ r; } ;
struct file {int dummy; } ;
struct TYPE_6__ {int /*<<< orphan*/  height; int /*<<< orphan*/  width; } ;
struct TYPE_7__ {TYPE_1__ pix; } ;
struct TYPE_8__ {TYPE_2__ fmt; } ;
struct TYPE_9__ {TYPE_3__ fmt; TYPE_5__ compose; } ;
struct capture_priv {TYPE_4__ vdev; } ;

/* Variables and functions */
 int EINVAL ; 
#define  V4L2_SEL_TGT_COMPOSE 131 
#define  V4L2_SEL_TGT_COMPOSE_BOUNDS 130 
#define  V4L2_SEL_TGT_COMPOSE_DEFAULT 129 
#define  V4L2_SEL_TGT_COMPOSE_PADDED 128 
 struct capture_priv* video_drvdata (struct file*) ; 

__attribute__((used)) static int capture_g_selection(struct file *file, void *fh,
			       struct v4l2_selection *s)
{
	struct capture_priv *priv = video_drvdata(file);

	switch (s->target) {
	case V4L2_SEL_TGT_COMPOSE:
	case V4L2_SEL_TGT_COMPOSE_DEFAULT:
	case V4L2_SEL_TGT_COMPOSE_BOUNDS:
		/* The compose rectangle is fixed to the source format. */
		s->r = priv->vdev.compose;
		break;
	case V4L2_SEL_TGT_COMPOSE_PADDED:
		/*
		 * The hardware writes with a configurable but fixed DMA burst
		 * size. If the source format width is not burst size aligned,
		 * the written frame contains padding to the right.
		 */
		s->r.left = 0;
		s->r.top = 0;
		s->r.width = priv->vdev.fmt.fmt.pix.width;
		s->r.height = priv->vdev.fmt.fmt.pix.height;
		break;
	default:
		return -EINVAL;
	}

	return 0;
}