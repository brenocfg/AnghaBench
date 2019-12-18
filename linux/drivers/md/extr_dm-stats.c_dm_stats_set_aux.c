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
struct dm_stats {int /*<<< orphan*/  mutex; } ;
struct dm_stat {char const* aux_data; } ;

/* Variables and functions */
 int ENOENT ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 struct dm_stat* __dm_stats_find (struct dm_stats*,int) ; 
 int /*<<< orphan*/  kfree (char const*) ; 
 char* kstrdup (char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int dm_stats_set_aux(struct dm_stats *stats, int id, const char *aux_data)
{
	struct dm_stat *s;
	const char *new_aux_data;

	mutex_lock(&stats->mutex);

	s = __dm_stats_find(stats, id);
	if (!s) {
		mutex_unlock(&stats->mutex);
		return -ENOENT;
	}

	new_aux_data = kstrdup(aux_data, GFP_KERNEL);
	if (!new_aux_data) {
		mutex_unlock(&stats->mutex);
		return -ENOMEM;
	}

	kfree(s->aux_data);
	s->aux_data = new_aux_data;

	mutex_unlock(&stats->mutex);

	return 0;
}