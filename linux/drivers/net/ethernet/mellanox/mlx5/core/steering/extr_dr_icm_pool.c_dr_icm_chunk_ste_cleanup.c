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
struct mlx5dr_icm_chunk {int /*<<< orphan*/  ste_arr; int /*<<< orphan*/  hw_ste_arr; int /*<<< orphan*/  miss_list; } ;

/* Variables and functions */
 int /*<<< orphan*/  kvfree (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void dr_icm_chunk_ste_cleanup(struct mlx5dr_icm_chunk *chunk)
{
	kvfree(chunk->miss_list);
	kvfree(chunk->hw_ste_arr);
	kvfree(chunk->ste_arr);
}