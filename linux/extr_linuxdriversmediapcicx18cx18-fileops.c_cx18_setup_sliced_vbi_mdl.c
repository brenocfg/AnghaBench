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
struct cx18_mdl {scalar_t__ readpos; int /*<<< orphan*/  bytesused; int /*<<< orphan*/ * curr_buf; } ;
struct cx18_buffer {scalar_t__ readpos; int /*<<< orphan*/  bytesused; int /*<<< orphan*/  buf; } ;
struct TYPE_2__ {int inserted_frame; int /*<<< orphan*/ * sliced_mpeg_size; int /*<<< orphan*/ * sliced_mpeg_data; struct cx18_buffer sliced_mpeg_buf; struct cx18_mdl sliced_mpeg_mdl; } ;
struct cx18 {TYPE_1__ vbi; } ;

/* Variables and functions */
 int CX18_VBI_FRAMES ; 

__attribute__((used)) static void cx18_setup_sliced_vbi_mdl(struct cx18 *cx)
{
	struct cx18_mdl *mdl = &cx->vbi.sliced_mpeg_mdl;
	struct cx18_buffer *buf = &cx->vbi.sliced_mpeg_buf;
	int idx = cx->vbi.inserted_frame % CX18_VBI_FRAMES;

	buf->buf = cx->vbi.sliced_mpeg_data[idx];
	buf->bytesused = cx->vbi.sliced_mpeg_size[idx];
	buf->readpos = 0;

	mdl->curr_buf = NULL;
	mdl->bytesused = cx->vbi.sliced_mpeg_size[idx];
	mdl->readpos = 0;
}