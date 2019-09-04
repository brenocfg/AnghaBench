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
struct mt9m111 {int /*<<< orphan*/  hdl; TYPE_1__* fmt; int /*<<< orphan*/  height; int /*<<< orphan*/  width; int /*<<< orphan*/  rect; int /*<<< orphan*/  ctx; } ;
struct TYPE_2__ {int /*<<< orphan*/  code; } ;

/* Variables and functions */
 int /*<<< orphan*/  mt9m111_set_context (struct mt9m111*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mt9m111_set_pixfmt (struct mt9m111*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mt9m111_setup_geometry (struct mt9m111*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  v4l2_ctrl_handler_setup (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void mt9m111_restore_state(struct mt9m111 *mt9m111)
{
	mt9m111_set_context(mt9m111, mt9m111->ctx);
	mt9m111_set_pixfmt(mt9m111, mt9m111->fmt->code);
	mt9m111_setup_geometry(mt9m111, &mt9m111->rect,
			mt9m111->width, mt9m111->height, mt9m111->fmt->code);
	v4l2_ctrl_handler_setup(&mt9m111->hdl);
}