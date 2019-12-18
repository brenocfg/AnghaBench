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
struct mlx5_ib_mcounters {int /*<<< orphan*/  mcntrs_mutex; scalar_t__ cntrs_max_index; int /*<<< orphan*/ * counters_data; } ;
struct ib_counters {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct mlx5_ib_mcounters* to_mcounters (struct ib_counters*) ; 

__attribute__((used)) static void counters_clear_description(struct ib_counters *counters)
{
	struct mlx5_ib_mcounters *mcounters = to_mcounters(counters);

	mutex_lock(&mcounters->mcntrs_mutex);
	kfree(mcounters->counters_data);
	mcounters->counters_data = NULL;
	mcounters->cntrs_max_index = 0;
	mutex_unlock(&mcounters->mcntrs_mutex);
}