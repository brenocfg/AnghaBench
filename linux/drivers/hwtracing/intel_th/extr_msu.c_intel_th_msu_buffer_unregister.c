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
struct msu_buffer_entry {int /*<<< orphan*/  entry; } ;
struct msu_buffer {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 struct msu_buffer_entry* __msu_buffer_entry_find (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct msu_buffer_entry*) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  msu_buffer_mutex ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

void intel_th_msu_buffer_unregister(const struct msu_buffer *mbuf)
{
	struct msu_buffer_entry *mbe;

	mutex_lock(&msu_buffer_mutex);
	mbe = __msu_buffer_entry_find(mbuf->name);
	if (mbe) {
		list_del(&mbe->entry);
		kfree(mbe);
	}
	mutex_unlock(&msu_buffer_mutex);
}