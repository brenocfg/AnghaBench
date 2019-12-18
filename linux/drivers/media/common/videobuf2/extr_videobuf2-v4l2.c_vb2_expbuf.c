#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct vb2_queue {int dummy; } ;
struct v4l2_exportbuffer {int /*<<< orphan*/  flags; int /*<<< orphan*/  plane; int /*<<< orphan*/  index; int /*<<< orphan*/  type; int /*<<< orphan*/  fd; } ;

/* Variables and functions */
 int vb2_core_expbuf (struct vb2_queue*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int vb2_expbuf(struct vb2_queue *q, struct v4l2_exportbuffer *eb)
{
	return vb2_core_expbuf(q, &eb->fd, eb->type, eb->index,
				eb->plane, eb->flags);
}