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
struct vchiq_mmal_instance {int /*<<< orphan*/  context_map_lock; int /*<<< orphan*/  context_map; } ;
struct mmal_msg_context {int handle; struct vchiq_mmal_instance* instance; } ;

/* Variables and functions */
 int ENOMEM ; 
 struct mmal_msg_context* ERR_PTR (int) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int idr_alloc (int /*<<< orphan*/ *,struct mmal_msg_context*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct mmal_msg_context*) ; 
 struct mmal_msg_context* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static struct mmal_msg_context *
get_msg_context(struct vchiq_mmal_instance *instance)
{
	struct mmal_msg_context *msg_context;
	int handle;

	/* todo: should this be allocated from a pool to avoid kzalloc */
	msg_context = kzalloc(sizeof(*msg_context), GFP_KERNEL);

	if (!msg_context)
		return ERR_PTR(-ENOMEM);

	/* Create an ID that will be passed along with our message so
	 * that when we service the VCHI reply, we can look up what
	 * message is being replied to.
	 */
	mutex_lock(&instance->context_map_lock);
	handle = idr_alloc(&instance->context_map, msg_context,
			   0, 0, GFP_KERNEL);
	mutex_unlock(&instance->context_map_lock);

	if (handle < 0) {
		kfree(msg_context);
		return ERR_PTR(handle);
	}

	msg_context->instance = instance;
	msg_context->handle = handle;

	return msg_context;
}