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
typedef  scalar_t__ u32 ;
struct v4l2_rect {int /*<<< orphan*/  top; int /*<<< orphan*/  left; int /*<<< orphan*/  height; int /*<<< orphan*/  width; } ;
struct mt9t112_priv {int num_formats; TYPE_1__* format; struct v4l2_rect frame; } ;
struct TYPE_2__ {scalar_t__ code; } ;

/* Variables and functions */
 int EINVAL ; 
 TYPE_1__* mt9t112_cfmts ; 
 int /*<<< orphan*/  mt9t112_frame_check (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int mt9t112_set_params(struct mt9t112_priv *priv,
			      const struct v4l2_rect *rect,
			      u32 code)
{
	int i;

	/*
	 * get color format
	 */
	for (i = 0; i < priv->num_formats; i++)
		if (mt9t112_cfmts[i].code == code)
			break;

	if (i == priv->num_formats)
		return -EINVAL;

	priv->frame  = *rect;

	/*
	 * frame size check
	 */
	mt9t112_frame_check(&priv->frame.width, &priv->frame.height,
			    &priv->frame.left, &priv->frame.top);

	priv->format = mt9t112_cfmts + i;

	return 0;
}