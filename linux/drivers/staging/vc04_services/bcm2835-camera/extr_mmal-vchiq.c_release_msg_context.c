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
struct mmal_msg_context {int /*<<< orphan*/  handle; struct vchiq_mmal_instance* instance; } ;

/* Variables and functions */
 int /*<<< orphan*/  idr_remove (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct mmal_msg_context*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
release_msg_context(struct mmal_msg_context *msg_context)
{
	struct vchiq_mmal_instance *instance = msg_context->instance;

	mutex_lock(&instance->context_map_lock);
	idr_remove(&instance->context_map, msg_context->handle);
	mutex_unlock(&instance->context_map_lock);
	kfree(msg_context);
}