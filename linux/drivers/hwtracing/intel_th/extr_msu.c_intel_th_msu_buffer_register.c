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
struct msu_buffer_entry {int /*<<< orphan*/  entry; struct module* owner; struct msu_buffer const* mbuf; } ;
struct msu_buffer {int /*<<< orphan*/  name; } ;
struct module {int dummy; } ;

/* Variables and functions */
 int EEXIST ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ __msu_buffer_entry_find (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct msu_buffer_entry*) ; 
 struct msu_buffer_entry* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  msu_buffer_list ; 
 int /*<<< orphan*/  msu_buffer_mutex ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

int intel_th_msu_buffer_register(const struct msu_buffer *mbuf,
				 struct module *owner)
{
	struct msu_buffer_entry *mbe;
	int ret = 0;

	mbe = kzalloc(sizeof(*mbe), GFP_KERNEL);
	if (!mbe)
		return -ENOMEM;

	mutex_lock(&msu_buffer_mutex);
	if (__msu_buffer_entry_find(mbuf->name)) {
		ret = -EEXIST;
		kfree(mbe);
		goto unlock;
	}

	mbe->mbuf = mbuf;
	mbe->owner = owner;
	list_add_tail(&mbe->entry, &msu_buffer_list);
unlock:
	mutex_unlock(&msu_buffer_mutex);

	return ret;
}