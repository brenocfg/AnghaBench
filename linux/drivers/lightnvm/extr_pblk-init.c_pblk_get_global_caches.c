#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  mutex; int /*<<< orphan*/  kref; } ;

/* Variables and functions */
 scalar_t__ kref_get_unless_zero (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kref_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 TYPE_1__ pblk_caches ; 
 int pblk_create_global_caches () ; 

__attribute__((used)) static int pblk_get_global_caches(void)
{
	int ret = 0;

	mutex_lock(&pblk_caches.mutex);

	if (kref_get_unless_zero(&pblk_caches.kref))
		goto out;

	ret = pblk_create_global_caches();
	if (!ret)
		kref_init(&pblk_caches.kref);

out:
	mutex_unlock(&pblk_caches.mutex);
	return ret;
}