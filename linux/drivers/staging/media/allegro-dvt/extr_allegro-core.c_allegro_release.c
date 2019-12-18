#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct file {int /*<<< orphan*/  private_data; } ;
struct TYPE_3__ {int /*<<< orphan*/  m2m_ctx; } ;
struct allegro_channel {TYPE_1__ fh; int /*<<< orphan*/  ctrl_handler; int /*<<< orphan*/  list; } ;

/* Variables and functions */
 struct allegro_channel* fh_to_channel (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct allegro_channel*) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  v4l2_ctrl_handler_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  v4l2_fh_del (TYPE_1__*) ; 
 int /*<<< orphan*/  v4l2_fh_exit (TYPE_1__*) ; 
 int /*<<< orphan*/  v4l2_m2m_ctx_release (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int allegro_release(struct file *file)
{
	struct allegro_channel *channel = fh_to_channel(file->private_data);

	v4l2_m2m_ctx_release(channel->fh.m2m_ctx);

	list_del(&channel->list);

	v4l2_ctrl_handler_free(&channel->ctrl_handler);

	v4l2_fh_del(&channel->fh);
	v4l2_fh_exit(&channel->fh);

	kfree(channel);

	return 0;
}