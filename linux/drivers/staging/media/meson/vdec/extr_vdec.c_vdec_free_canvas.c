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
struct amvdec_session {int canvas_num; int /*<<< orphan*/ * canvas_alloc; TYPE_1__* core; } ;
struct TYPE_2__ {int /*<<< orphan*/  canvas; } ;

/* Variables and functions */
 int /*<<< orphan*/  meson_canvas_free (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void vdec_free_canvas(struct amvdec_session *sess)
{
	int i;

	for (i = 0; i < sess->canvas_num; ++i)
		meson_canvas_free(sess->core->canvas, sess->canvas_alloc[i]);

	sess->canvas_num = 0;
}