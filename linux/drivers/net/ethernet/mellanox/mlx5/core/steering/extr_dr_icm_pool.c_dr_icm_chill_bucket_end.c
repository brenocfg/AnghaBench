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
struct mlx5dr_icm_bucket {scalar_t__ sync_list_count; int /*<<< orphan*/  free_list_count; int /*<<< orphan*/  free_list; int /*<<< orphan*/  sync_list; } ;

/* Variables and functions */
 int /*<<< orphan*/  list_splice_tail_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void dr_icm_chill_bucket_end(struct mlx5dr_icm_bucket *bucket)
{
	list_splice_tail_init(&bucket->sync_list, &bucket->free_list);
	bucket->free_list_count += bucket->sync_list_count;
	bucket->sync_list_count = 0;
}