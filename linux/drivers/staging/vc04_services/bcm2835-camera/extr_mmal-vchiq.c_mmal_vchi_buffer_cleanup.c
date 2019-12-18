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
struct mmal_msg_context {int dummy; } ;
struct mmal_buffer {struct mmal_msg_context* msg_context; } ;

/* Variables and functions */
 int /*<<< orphan*/  release_msg_context (struct mmal_msg_context*) ; 

int mmal_vchi_buffer_cleanup(struct mmal_buffer *buf)
{
	struct mmal_msg_context *msg_context = buf->msg_context;

	if (msg_context)
		release_msg_context(msg_context);
	buf->msg_context = NULL;

	return 0;
}