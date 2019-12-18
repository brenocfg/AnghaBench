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
struct mapped_device {int dummy; } ;
struct dm_table {struct mapped_device* md; int /*<<< orphan*/  mode; int /*<<< orphan*/  type; int /*<<< orphan*/  target_callbacks; int /*<<< orphan*/  devices; } ;
typedef  int /*<<< orphan*/  fmode_t ;

/* Variables and functions */
 int /*<<< orphan*/  DM_TYPE_NONE ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 unsigned int KEYS_PER_NODE ; 
 scalar_t__ alloc_targets (struct dm_table*,unsigned int) ; 
 unsigned int dm_round_up (unsigned int,unsigned int) ; 
 int /*<<< orphan*/  kfree (struct dm_table*) ; 
 struct dm_table* kzalloc (int,int /*<<< orphan*/ ) ; 

int dm_table_create(struct dm_table **result, fmode_t mode,
		    unsigned num_targets, struct mapped_device *md)
{
	struct dm_table *t = kzalloc(sizeof(*t), GFP_KERNEL);

	if (!t)
		return -ENOMEM;

	INIT_LIST_HEAD(&t->devices);
	INIT_LIST_HEAD(&t->target_callbacks);

	if (!num_targets)
		num_targets = KEYS_PER_NODE;

	num_targets = dm_round_up(num_targets, KEYS_PER_NODE);

	if (!num_targets) {
		kfree(t);
		return -ENOMEM;
	}

	if (alloc_targets(t, num_targets)) {
		kfree(t);
		return -ENOMEM;
	}

	t->type = DM_TYPE_NONE;
	t->mode = mode;
	t->md = md;
	*result = t;
	return 0;
}