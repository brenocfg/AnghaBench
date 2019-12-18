#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_4__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct vchiq_state {int dummy; } ;
struct inode {int dummy; } ;
struct file {TYPE_1__* private_data; } ;
typedef  TYPE_1__* VCHIQ_INSTANCE_T ;
struct TYPE_6__ {int /*<<< orphan*/  tgid; } ;
struct TYPE_5__ {int /*<<< orphan*/  bulk_waiter_list; int /*<<< orphan*/  bulk_waiter_list_mutex; int /*<<< orphan*/  completion_mutex; int /*<<< orphan*/  remove_event; int /*<<< orphan*/  insert_event; int /*<<< orphan*/  pid; struct vchiq_state* state; } ;

/* Variables and functions */
 int ENOMEM ; 
 int ENOTCONN ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 TYPE_4__* current ; 
 int /*<<< orphan*/  init_completion (int /*<<< orphan*/ *) ; 
 TYPE_1__* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vchiq_arm_log_level ; 
 int /*<<< orphan*/  vchiq_debugfs_add_instance (TYPE_1__*) ; 
 struct vchiq_state* vchiq_get_state () ; 
 int /*<<< orphan*/  vchiq_log_error (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  vchiq_log_info (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int vchiq_open(struct inode *inode, struct file *file)
{
	struct vchiq_state *state = vchiq_get_state();
	VCHIQ_INSTANCE_T instance;

	vchiq_log_info(vchiq_arm_log_level, "vchiq_open");

	if (!state) {
		vchiq_log_error(vchiq_arm_log_level,
				"vchiq has no connection to VideoCore");
		return -ENOTCONN;
	}

	instance = kzalloc(sizeof(*instance), GFP_KERNEL);
	if (!instance)
		return -ENOMEM;

	instance->state = state;
	instance->pid = current->tgid;

	vchiq_debugfs_add_instance(instance);

	init_completion(&instance->insert_event);
	init_completion(&instance->remove_event);
	mutex_init(&instance->completion_mutex);
	mutex_init(&instance->bulk_waiter_list_mutex);
	INIT_LIST_HEAD(&instance->bulk_waiter_list);

	file->private_data = instance;

	return 0;
}