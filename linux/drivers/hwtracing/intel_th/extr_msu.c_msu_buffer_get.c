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
struct msu_buffer_entry {struct msu_buffer const* mbuf; int /*<<< orphan*/  owner; } ;
struct msu_buffer {int dummy; } ;

/* Variables and functions */
 struct msu_buffer_entry* __msu_buffer_entry_find (char const*) ; 
 int /*<<< orphan*/  msu_buffer_mutex ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  try_module_get (int /*<<< orphan*/ ) ; 

__attribute__((used)) static const struct msu_buffer *
msu_buffer_get(const char *name)
{
	struct msu_buffer_entry *mbe;

	mutex_lock(&msu_buffer_mutex);
	mbe = __msu_buffer_entry_find(name);
	if (mbe && !try_module_get(mbe->owner))
		mbe = NULL;
	mutex_unlock(&msu_buffer_mutex);

	return mbe ? mbe->mbuf : NULL;
}