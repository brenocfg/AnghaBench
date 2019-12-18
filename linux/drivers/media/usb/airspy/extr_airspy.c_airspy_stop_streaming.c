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
struct airspy {int /*<<< orphan*/  v4l2_lock; int /*<<< orphan*/  flags; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  CMD_RECEIVER_MODE ; 
 int /*<<< orphan*/  POWER_ON ; 
 int /*<<< orphan*/  airspy_cleanup_queued_bufs (struct airspy*) ; 
 int /*<<< orphan*/  airspy_ctrl_msg (struct airspy*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  airspy_free_stream_bufs (struct airspy*) ; 
 int /*<<< orphan*/  airspy_free_urbs (struct airspy*) ; 
 int /*<<< orphan*/  airspy_kill_urbs (struct airspy*) ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct airspy* vb2_get_drv_priv (struct vb2_queue*) ; 

__attribute__((used)) static void airspy_stop_streaming(struct vb2_queue *vq)
{
	struct airspy *s = vb2_get_drv_priv(vq);

	dev_dbg(s->dev, "\n");

	mutex_lock(&s->v4l2_lock);

	/* stop hardware streaming */
	airspy_ctrl_msg(s, CMD_RECEIVER_MODE, 0, 0, NULL, 0);

	airspy_kill_urbs(s);
	airspy_free_urbs(s);
	airspy_free_stream_bufs(s);

	airspy_cleanup_queued_bufs(s);

	clear_bit(POWER_ON, &s->flags);

	mutex_unlock(&s->v4l2_lock);
}