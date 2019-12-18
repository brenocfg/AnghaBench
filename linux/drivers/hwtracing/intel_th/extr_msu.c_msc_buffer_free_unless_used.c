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
struct msc {int /*<<< orphan*/  buf_mutex; } ;

/* Variables and functions */
 int msc_buffer_unlocked_free_unless_used (struct msc*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int msc_buffer_free_unless_used(struct msc *msc)
{
	int ret;

	mutex_lock(&msc->buf_mutex);
	ret = msc_buffer_unlocked_free_unless_used(msc);
	mutex_unlock(&msc->buf_mutex);

	return ret;
}