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
struct vb2_buffer {int dummy; } ;
struct imgu_device {int /*<<< orphan*/  lock; } ;
typedef  enum vb2_buffer_state { ____Placeholder_vb2_buffer_state } vb2_buffer_state ;

/* Variables and functions */
 int /*<<< orphan*/  imgu_v4l2_buffer_done (struct vb2_buffer*,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void imgu_buffer_done(struct imgu_device *imgu, struct vb2_buffer *vb,
			     enum vb2_buffer_state state)
{
	mutex_lock(&imgu->lock);
	imgu_v4l2_buffer_done(vb, state);
	mutex_unlock(&imgu->lock);
}