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
struct vb2_buffer {int /*<<< orphan*/  vb2_queue; } ;
struct sur40_state {int /*<<< orphan*/  qlock; int /*<<< orphan*/  buf_list; } ;
struct sur40_buffer {int /*<<< orphan*/  list; } ;

/* Variables and functions */
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 struct sur40_state* vb2_get_drv_priv (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void sur40_buffer_queue(struct vb2_buffer *vb)
{
	struct sur40_state *sur40 = vb2_get_drv_priv(vb->vb2_queue);
	struct sur40_buffer *buf = (struct sur40_buffer *)vb;

	spin_lock(&sur40->qlock);
	list_add_tail(&buf->list, &sur40->buf_list);
	spin_unlock(&sur40->qlock);
}