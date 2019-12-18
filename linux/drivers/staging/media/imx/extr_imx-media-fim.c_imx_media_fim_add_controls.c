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
struct imx_media_fim {int /*<<< orphan*/  ctrl_handler; TYPE_1__* sd; } ;
struct TYPE_2__ {int /*<<< orphan*/  ctrl_handler; } ;

/* Variables and functions */
 int v4l2_ctrl_add_handler (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 

int imx_media_fim_add_controls(struct imx_media_fim *fim)
{
	/* add the FIM controls to the calling subdev ctrl handler */
	return v4l2_ctrl_add_handler(fim->sd->ctrl_handler,
				     &fim->ctrl_handler, NULL, false);
}