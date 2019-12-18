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
typedef  int /*<<< orphan*/  u8 ;
struct amvdec_session {scalar_t__ canvas_num; int /*<<< orphan*/ * canvas_alloc; TYPE_1__* core; } ;
struct TYPE_2__ {int /*<<< orphan*/  canvas; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int ENOMEM ; 
 scalar_t__ MAX_CANVAS ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int meson_canvas_alloc (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int canvas_alloc(struct amvdec_session *sess, u8 *canvas_id)
{
	int ret;

	if (sess->canvas_num >= MAX_CANVAS) {
		dev_err(sess->core->dev, "Reached max number of canvas\n");
		return -ENOMEM;
	}

	ret = meson_canvas_alloc(sess->core->canvas, canvas_id);
	if (ret)
		return ret;

	sess->canvas_alloc[sess->canvas_num++] = *canvas_id;
	return 0;
}