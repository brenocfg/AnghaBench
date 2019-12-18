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
typedef  int /*<<< orphan*/  u32 ;
struct mlx5_devx_event_table {int /*<<< orphan*/  event_xa; } ;
struct devx_obj_event {int /*<<< orphan*/  obj_sub_list; int /*<<< orphan*/  object_ids; int /*<<< orphan*/  unaffiliated_list; } ;
struct devx_event {int /*<<< orphan*/  obj_sub_list; int /*<<< orphan*/  object_ids; int /*<<< orphan*/  unaffiliated_list; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct devx_obj_event*) ; 
 struct devx_obj_event* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xa_init (int /*<<< orphan*/ *) ; 
 int xa_insert (int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct devx_obj_event*,int /*<<< orphan*/ ) ; 
 struct devx_obj_event* xa_load (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
subscribe_event_xa_alloc(struct mlx5_devx_event_table *devx_event_table,
			 u32 key_level1,
			 bool is_level2,
			 u32 key_level2)
{
	struct devx_obj_event *obj_event;
	struct devx_event *event;
	int err;

	event = xa_load(&devx_event_table->event_xa, key_level1);
	if (!event) {
		event = kzalloc(sizeof(*event), GFP_KERNEL);
		if (!event)
			return -ENOMEM;

		INIT_LIST_HEAD(&event->unaffiliated_list);
		xa_init(&event->object_ids);

		err = xa_insert(&devx_event_table->event_xa,
				key_level1,
				event,
				GFP_KERNEL);
		if (err) {
			kfree(event);
			return err;
		}
	}

	if (!is_level2)
		return 0;

	obj_event = xa_load(&event->object_ids, key_level2);
	if (!obj_event) {
		obj_event = kzalloc(sizeof(*obj_event), GFP_KERNEL);
		if (!obj_event)
			/* Level1 is valid for future use, no need to free */
			return -ENOMEM;

		err = xa_insert(&event->object_ids,
				key_level2,
				obj_event,
				GFP_KERNEL);
		if (err)
			return err;
		INIT_LIST_HEAD(&obj_event->obj_sub_list);
	}

	return 0;
}